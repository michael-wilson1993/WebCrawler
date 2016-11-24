#include "WebScraper.h"
#include <iostream>
#include <string>





// write function for libcurl
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}


bool WebScraper::imageScraper(std::string link)
{
   //const int FILENAME_MAX = 250;
   std::string forbidChar = "/";
    CURL* curl;
    FILE* fp;
    CURLcode res;
    bool flag = false;
    char outfilename[FILENAME_MAX];


    int xx;
    for(int x = 0; x < link.size(); x++)
    {
        if(link[x] != '/')
            outfilename[x] = link[x];
        else
            outfilename[x] = '_';
        flag = false;
       xx = x;
    }

    outfilename[0]='i';
    outfilename[1]='m';
    outfilename[2]='g';
    outfilename[3]='/';

       curl = curl_easy_init();
    if (curl)
    {
       fp = fopen(outfilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return true;
}


WebScraper::WebScraper(std::string link, int level, std::set<std::string> &links)
{
  if(links.find(link) == links.end())
   if(level != 0)
   {
    updateLinkFile(link);

    links.insert(link);
    std::cout << "\n\n\n\n" << "level: " << level << "\n";
    std::cout << "connecting to: " << link << '\n\n\n';
    WebScraper *tempCrawler;
    init(link, level);
    linkOfLists = scrape(s);
    for (int x = 0; x < linkOfLists.size(); x++)
    {
      tempCrawler = new WebScraper(linkOfLists[x], level-1, links);
      delete tempCrawler;
    }
  }
}
/*
    std::cout << "\n\n ---- current list of visited links ---- \n\n";
    for (std::set<std::string>::iterator i = links.begin(); i != links.end(); i++) 
      std::cout << *i << "\n";
    std::cout << "\n\n ---- end ---- \n\n";
    */
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
   curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
   curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

       //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
   curl_easy_setopt (curl, CURLOPT_PORT , 80);
	     //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
//	curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
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

std::string grabImageLink(std::string file, int index)
{
  int x = index, y = index;
  std::string ret;
  while(file[x] != '"')
    x--;
  x++;
  while(file[x] != '"')
  {
    ret += file[x];
    x++;
  }
  return ret;
}

std::vector<std::string> WebScraper::scrape(std::string s)
{
  std::vector<std::string> ret;
  int x = 0 ,y;
  int size = s.size();
  bool refFound = false;
  std::string temp;
  while(x < size)
  {
    //finding images

    if(x > 10)
    {
      std::string imageTemp = "";
      if(s[x-1] == 'g' && s[x-2] == 'n' && s[x-3] == 'p' && s[x-4] == '.')
      {
        if(s[x] == '"' || s[x] == '/')
        {
          imageScraper(grabImageLink(s, x));
        }
      }




        //if (temp[temp.size()-4] == '.' && temp[temp.size()-3] == 'j' && temp[temp.size()-2] == 'p' && temp[temp.size()-1] == 'g')
         // imageScraper imageDownload(temp);
        //if (temp[temp.size()-4] == '.' && temp[temp.size()-3] == 'p' && temp[temp.size()-2] == 'n' && temp[temp.size()-1] == 'g')
         // imageScraper imageDownload(temp);
        //if (temp[temp.size()-5] == '.' && temp[temp.size()-4] == 'j' && temp[temp.size()-3] == 'p' && temp[temp.size()-2] == 'e' && temp[temp.size()-1] == 'g')
         /// imageScraper imageDownload(temp);
    }
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
        if (temp[0] == 'h' && temp[3] == 'p' && temp[temp.size()-1] == '/')
          ret.push_back(temp);
      }
    }
    x++;
  }
  return ret;
}

void WebScraper::updateLinkFile(std::string link)
{
  std::ofstream fout;
  fout.open("VisitedLinks", std::ofstream::out | std::ofstream::app);
  fout << link << std::endl;
  fout.close();
}