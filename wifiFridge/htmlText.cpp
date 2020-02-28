#include "htmlText.h"

const char* ok = "HTTP/1.1 200 OK\nContent-type:text/html\nConnection: close\n\n";
const char* htmlHeader = "<!DOCTYPE html><html>\n<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
                          <link rel=\"icon\" href=\"data:,\">\n\
                          <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
const char* textCss = "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>";
const char* title = "<body><h1>Vault coolant system</h1>";
const char* coolerOn = "";
const char* coolerOff = "";

const char* htmlResponseOk(void)
{
  return ok;
}

const char* htmlHeading(void)
{
  return htmlHeader;
}

const char* htmlTextCss(void)
{
  return textCss;
}

const char* htmlTitle(void)
{
  return title;
}
