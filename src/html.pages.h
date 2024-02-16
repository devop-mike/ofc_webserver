#include "html.pages.struct.h"
#include "html.pages.data.h"

const unsigned int iHtmlPageCount = sizeof(pagedata) / sizeof(PAGE_DATA);

PAGE_DATA *HtmlFindPage(String path)
{
  PAGE_DATA *ptrPageData = (PAGE_DATA *)pagedata;
  for (int i = 0; i < iHtmlPageCount; i++, ptrPageData++)
  {
    if (ptrPageData->path == path)
    {
      return ptrPageData;
    }
  }
  return NULL;
}

void HtmlSendPage404(Stream &stream)
{
  stream.println("HTTP/1.1 404 Not found");
  stream.println("Content-Length: 13");
  stream.println("Content-type: text/plain");
  stream.println();
  stream.println("404 Not found");
  stream.println();
}

void chunkedwrite(Stream &stream, const uint8_t *buffer, size_t size)
{ // chunk large files and yield so stream.write doesn't lock up mcu.
  const size_t chunksize = 4000;
  const uint8_t *data = buffer;
  size_t length = size;
  while (length > chunksize)
  {
    stream.write(data, chunksize);
    length -= chunksize;
    data += chunksize;
    yield();
    Serial.print("left: ");
    Serial.println(length);
  }
  stream.write(data, length);
}

void HtmlSendPage200(Stream &stream, PAGE_DATA *ptrPageData)
{
  // Serial.print("path: ");
  // Serial.println(ptrPageData->path);
  // Serial.print("mime: ");
  // Serial.println(ptrPageData->mime);
  // Serial.print("length: ");
  // Serial.println(ptrPageData->length);

  stream.println("HTTP/1.1 200 OK");
  stream.println("Content-Encoding: gzip");
  stream.print("Content-Length: ");
  stream.println(ptrPageData->length);
  stream.print("Content-type: ");
  stream.println(ptrPageData->mime);
  stream.println();
  chunkedwrite(stream, ptrPageData->data, ptrPageData->length);
  stream.println();
}

// void HtmlSendPage200gunzip(Stream &stream, PAGE_DATA *ptrPageData)
// {
//   unsigned long buffsize = sizeof(buffer);
//   // uncompress(buffer, &buffsize, ptrPageData->data, ptrPageData->length);
//   stream.println("HTTP/1.1 200 OK");
//   stream.print("Content-Length: ");
//   stream.println(buffsize);
//   stream.println("Content-type: text/html");
//   stream.println();
//   stream.write(buffer, buffsize);
//   stream.println();
// }