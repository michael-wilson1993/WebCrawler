#include "WebScraper.h"
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <termcap.h>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include "imgLoader.h"
#include <opencv2/opencv.hpp>




// write function for libcurl
size_t callbackfunction(void *ptr, size_t size, size_t nmemb, void* userdata)
{
    FILE* stream = (FILE*)userdata;
    if (!stream)
    {
        printf("!!! No stream\n");
        return 0;
    }

    size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
    return written;
}


bool WebScraper::imageScraper(std::string link)
{
    std::string strng =  link;

    for(int x = 0; x < strng.size(); x++)
      if(strng[x] == '/')
        strng[x] = '_';

      std::string str = "img/" + strng;



    FILE* fp = fopen(str.c_str(), "wb");
    if (!fp)
    {
        printf("!!! Failed to create file on the disk\n");
        return false;
    }

    CURL* curlCtx = curl_easy_init();
    curl_easy_setopt(curlCtx, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curlCtx, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curlCtx, CURLOPT_WRITEFUNCTION, callbackfunction);
    curl_easy_setopt(curlCtx, CURLOPT_FOLLOWLOCATION, 1);

    CURLcode rc = curl_easy_perform(curlCtx);
    if (rc)
    {
        printf("!!! Failed to download: %s\n", link.c_str());
        return false;
    }

    long res_code = 0;
    curl_easy_getinfo(curlCtx, CURLINFO_RESPONSE_CODE, &res_code);
    if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK))
    {
        printf("!!! Response code: %d\n", res_code);
        return false;
    }

    curl_easy_cleanup(curlCtx);

    fclose(fp);

    imgLoader img;
    cv::Mat im;
    im = img.loadImage(str);
    cv::namedWindow("w", cv::WINDOW_AUTOSIZE);
    cv::imshow("w", im);
    cv::waitKey(0);  

    return true;

}


WebScraper::WebScraper(std::string link, int level, std::set<std::string> &links)
{
  system("clear");
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

bool checkHREF(std::string file, int index)
{
  int x = index;
  while(file[x] != '"')
    x--;

  std::ofstream outf("outputs.txt", std::ofstream::out | std::ofstream::app);

  for(int y = 0; y < 9; y ++)
     outf << file[x-y];
   outf << std::endl;
   outf.close();

  if(file[x-1] == '='
    && file[x-2] == 'c' 
    && file[x+1] == 'h'
    && file[x+4] == 'p') // c
    return true;
  return false;
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

      if(s[x-1] == 'g' && s[x-2] == 'n' && s[x-3] == 'p' && s[x-4] == '.')
      {
        if(checkHREF(s, x-2))
          imageScraper(grabImageLink(s, x-2));
      }


      if(s[x-1] == 'g' && s[x-2] == 'p' && s[x-3] == 'j' && s[x-4] == '.')
      {
        if(checkHREF(s, x-2))
          imageScraper(grabImageLink(s, x-2));
      }
    }
    
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