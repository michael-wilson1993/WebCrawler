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

std::string getExtension(std::string link)
{
   // gets the picture extension so that it can add it back in the future
  for(int x = 3; x < link.size(); x++)
  {
    if (link[x- 3] == '.' && link[x- 2] == 'j' && link[x-1] == 'p' && link[x] == 'g')
      return ".jpg";
    if (link[x- 3] == '.' && link[x- 2] == 'p' && link[x-1] == 'n' && link[x] == 'g')
      return ".png";
  }
}

bool WebScraper::downloadToTemp(std::string link)
{
  std::string strng =  link;

  // avoids facebook links
  if(link.find("facebook")!= std::string::npos)
    return false;

  // renames with underscores for file naming as slashes arent allowed
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

    // libcurl initialization functions
    CURL* curlCtx = curl_easy_init();
    curl_easy_setopt(curlCtx, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curlCtx, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curlCtx, CURLOPT_WRITEFUNCTION, callbackfunction);
    curl_easy_setopt(curlCtx, CURLOPT_FOLLOWLOCATION, 1);

    // outputs message if message fails to be downloaded
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

    // checks if file was renamed properly
    std::string nameWE = "img/temp" + getExtension(link);
    if (rename(str.c_str(), nameWE.c_str()) == 0)
       std::cout << "\n\nfile successfully renamed\n\n";
    else
       std::cout << "\n\nError renaming file\n\n";

    imgLoader img;
    img.displayImage(nameWE);

}
bool WebScraper::imageScraper(std::string link, std::vector<std::string> &picName)
{
   std::string strng =  link;

   if(link.find("facebook")!= std::string::npos)
      return false;

   for(int x = 0; x < strng.size(); x++)
      if(strng[x] == '/')
	 strng[x] = '_';

   std::string str = "img/" + strng;

   for(int x = 0; x < picName.size(); x++)
      if (picName[x] == str)
	 return false;

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
   std::string newName = img.hashImage(str, 6), startNewName = "img/";
   if(newName == "")
      return false;
   startNewName += newName + getExtension(str);

   std::vector<std::string>::iterator it = std::find(picName.begin(), picName.end(), startNewName);
   if( it == picName.end())
   {
      img.displayImage(str);
      picName.push_back(startNewName);
      std::sort (picName.begin(), picName.end());
      updateImageFile(startNewName);
      imageKeyFile(startNewName, link);
      //sleep(.5);
   } 
   else
   {
      int x;
      std::cout << "duplicates found\n\n" << str; 
      img.displayImage(str, *it);
      //sleep(.5);
   }

   if (rename(str.c_str(), startNewName.c_str()) == 0)
      std::cout << "\n\nfile successfully renamed\n\n";
   else
      std::cout << "\n\nError renaming file\n\n";

   return true;


}


WebScraper::WebScraper(std::string link, int level, std::set<std::string> &links, std::vector<std::string> &imageNames)
{
   system("clear");
   if(links.find(link) == links.end())
      if(level != 0)
      {
	 // changes link name so it fits with our naming scheme
	 updateLinkFile(link);
         // insert link into visited link storage
	 links.insert(link);
	 std::cout << "\n\n\n\n" << "level: " << level << "\n";
	 std::cout << "connecting to: " << link << '\n\n\n';
	 
	 WebScraper *tempCrawler;
	 init(link, level);
	 linkOfLists = scrape(s, imageNames);
	 for (int x = 0; x < linkOfLists.size(); x++)
	 {
	    // nests search to continue to lower depths
	    tempCrawler = new WebScraper(linkOfLists[x], level-1, links, imageNames);
	    delete tempCrawler;
	 }
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
      return 0;
   }

   std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
   return size*nmemb;
}

bool WebScraper::init(std::string link, int level)
{
   // functions related to initializing the libcurl library
   curl_global_init(CURL_GLOBAL_DEFAULT);
   curl = curl_easy_init();
   if(curl)
   {
      curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
      curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
      curl_easy_setopt (curl, CURLOPT_PORT , 80);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
      res = curl_easy_perform(curl);


      if(res != CURLE_OK)
      {
	 fprintf(stderr, "curl_easy_perform() failed: %s\n",
		 curl_easy_strerror(res));
      }


      curl_easy_cleanup(curl);
   }
}

std::string grabImageLink(std::string file, int index)
{
   int x = index, y = index;
   std::string ret;
   // checks for " key to know where a link will be located
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
   // checks keys around the href to make sure they fit the schema
   int x = index;
   while(file[x] != '"')
      x--;

   if(file[x-1] == '='
      && file[x-2] == 'c' 
      && file[x+1] == 'h'
      && file[x+4] == 'p') // c
      return true;
   return false;
}

    std::vector<std::string> WebScraper::scrape(std::string s, std::vector<std::string> &picName)
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
              imageScraper(grabImageLink(s, x-2), picName);
          }


          if(s[x-1] == 'g' && s[x-2] == 'p' && s[x-3] == 'j' && s[x-4] == '.')
          {
            if(checkHREF(s, x-2))
              imageScraper(grabImageLink(s, x-2), picName);
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
   // updates the link name in the file
  std::ofstream fout;
  fout.open("logFiles/VisitedLinks", std::ofstream::out | std::ofstream::app);
  fout << link << std::endl;
  fout.close();
}

void WebScraper::updateImageFile(std::string link)
{
   // updates the image name after the hash
  std::ofstream fout;
  fout.open("logFiles/savedImages", std::ofstream::out | std::ofstream::app);
  fout << link << std::endl;
  fout.close();
}


void WebScraper::imageKeyFile(std::string key, std::string link)
{
   // creates a look up table with all the image links
  std::ofstream fout;
  fout.open("logFiles/lookUpTable.txt", std::ofstream::out | std::ofstream::app);
  fout << key << "|" << link <<  std::endl;
  fout.close();
}
