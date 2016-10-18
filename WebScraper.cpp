#include "WebScraper.h"


WebScraper::WebScraper(std::string link, int level, std::vector<std::string> &links)
{
   if(level != 0)
   {
      WebScraper *tempCrawler;
      init(link, level);
      linkOfLists = scrape(s);
     for (int x = 0; x < linkOfLists.size(); x++)
     {
	     tempCrawler = new WebScraper(linkOfLists[x], level-1, links);
       delete tempCrawler;
     }
      //if(linkOfLists.size() > 0)
	     links.insert( links.end(), linkOfLists.begin(), linkOfLists.end() );
   }
   

}
size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try
    {
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e)
    {
        //handle memory problem
        return 0;
    }

    std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    return size*nmemb;
}

bool WebScraper::init(std::string link, int level)
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
    if(curl)
    {

       curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
       curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
       
       //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
	     curl_easy_setopt (curl, CURLOPT_PORT , 80);
	     //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        //curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L); //remove this to disable verbose output
	

        /* Perform the request, res will get the return code */
	 res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
}



std::vector<std::string> WebScraper::scrape(std::string s)
{
  std::vector<std::string> ret;
  int x = 0;
  int size = s.size();
  bool refFound = false;
  std::string temp;
  while(x < size)
  {
    //cout << x << "/" << size <<  endl;
    if (!refFound)
    {
      if (s[x] == 'h' && s[x+1] == 'r' && s[x+2] == 'e' && s[x+3] == 'f')
      {
        refFound = true;
      }
    }
    else
    {
      if(s[x] == 39)
        refFound = false;
      else if(s[x] == '"') // 39 is the ascci value is (')
      {
        temp = ""; // clear the string for new link
        x++; // incriment by one to get off the '"' character...
        while(s[x] != '"')
        {
          temp += s[x];
          x++;
        }
        refFound = false;
        if (temp[0] == 'h' && temp[3] == 'p')
          ret.push_back(temp);
      }
    }
    x++;
  }
  return ret;
}
