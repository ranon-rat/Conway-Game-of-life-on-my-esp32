#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "static.hpp"
#include "conway.hpp"
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
void handleWebSocketMessage(Conway *c, void *arg, uint8_t *data, size_t len)
{
    // i will receive something close to
    // t123
    // so lets try to do this XD
    if (len > 4)
        return;
    bool first_val = ((char)data[0]) == 't';
    char msg[len];
    // so with this i just move in the pointer?
    // i hope it works XD
    memcpy(msg, data + 1, len - 1);
    Serial.println(msg);
    msg[len - 1] = '\0';
    int value = atoi(msg);
    c->update_cell(value, first_val);
    if (ws.count() > 0)
    {
        char *map = c->map_to_char();
        ws.textAll(map);
    }
}

void onEvent(Conway *c, AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case WS_EVT_DATA:
        handleWebSocketMessage(c, arg, data, len);
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}
void initWebSocket(Conway *c)
{
    ws.onEvent([c](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                   void *arg, uint8_t *data, size_t len)
               { onEvent(c, server, client, type, arg, data, len); });
    server.addHandler(&ws);
}
void StartServer(Conway *c)
{
    initWebSocket(c);

    server.on("/", [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", index_html); });
    // veamos si aqui funciona

    server.on("/map", [c](AsyncWebServerRequest *request)
              {
                  char *map = c->map_to_char();
                  request->send_P(200, "text/*", map);
              });
    server.begin();
}