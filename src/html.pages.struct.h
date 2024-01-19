#pragma once

typedef struct PAGE_DATA
{
  char *path;
  const char *mime;
  const unsigned char *data;
  size_t length;
};

const char *mime_css = "text/css";
const char *mime_html = "text/html";
const char *mime_js = "text/javascript";
const char *mime_json = "application/json";
const char *mime_plain = "text/plain";
const char *mime_png = "image/png";
const char *mime_svg = "image/svg+xml";
const char *mime_xml = "text/xml";
