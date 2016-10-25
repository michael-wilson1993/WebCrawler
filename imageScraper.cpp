#include "imageScraper.h"

// write function for libcurl
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}


imageScraper::imageScraper(std::string link)
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
    
	/*
	CURL *curl;
    FILE *fp;
    CURLcode res;
    char outfilename[FILENAME_MAX] = "page.html";
    curl = curl_easy_init();                                                                                                                                                                                                                                                           
    if (curl)
    {   
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }   
    */
}
