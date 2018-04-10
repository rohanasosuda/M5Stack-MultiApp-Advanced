#include "../apps.h"


unsigned long counter;

void AP_Mode()
{
    WiFi.disconnect();
    delay(200);
    WiFi.mode(WIFI_MODE_AP);
    WiFi.begin("M5Stack");
    WiFi.softAPsetHostname("M5Stack");
    M5.Lcd.drawString("AP Mode Started", 5, 50, 2);
    M5.Lcd.drawString("Host Name: M5Stack", 5, 70, 2);
    M5.Lcd.drawString("IP Address: " + WiFi.softAPIP().toString(), 5, 90, 2);
}

void STA_Mode()
{
    WiFi.disconnect();
    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin();
    M5.Lcd.drawString("STA Mode Started", 5, 50, 2);
    M5.Lcd.drawString("Will Connect to sored SSID", 5, 70, 2);
}

void appWiFiSetup()
{
    MyMenu.drawAppMenu(F("WiFi"), F("ESC"), F("SELECT"), F("LIST"));

    while (M5.BtnB.wasPressed())
    {
        M5.update();
    }

    MyMenu.clearList();
    MyMenu.setListCaption("WiFi");
    MyMenu.addList("WiFi STA");
    MyMenu.addList("WPS Button");
    MyMenu.addList("WPS Pin Code");
    MyMenu.addList("WiFi AP");
    MyMenu.addList("WiFi OFF");
    MyMenu.showList();

    while (!M5.BtnA.wasPressed())
    {
        if (M5.BtnC.wasPressed())
        {
            MyMenu.nextList();
        }
        if (M5.BtnB.wasPressed())
        {
            if (MyMenu.getListString() == "WiFi STA")
            {
                MyMenu.windowClr();
                delay(200);
                STA_Mode();
                while (!M5.BtnA.wasPressed())
                {
                    M5.update();
                }
                MyMenu.windowClr();
                MyMenu.drawAppMenu(F("WiFi"), F("ESC"), F("SELECT"), F("LIST"));
                MyMenu.showList();
            }
             if (MyMenu.getListString() == "WiFi AccessPoint")
            {
                MyMenu.windowClr();
                delay(200);
                AP_Mode();
                while (!M5.BtnA.wasPressed())
                {
                    M5.update();
                }
                MyMenu.windowClr();
                MyMenu.drawAppMenu(F("WiFi"), F("ESC"), F("SELECT"), F("LIST"));
                MyMenu.showList();
            }
            if (MyMenu.getListString() == "WPS Button")
            {
                MyMenu.windowClr();
                delay(200);
                Wps_run(true);
                while (!WiFi.isConnected())
                {
                    M5.update();
                    delay(50);
                    counter++;
                    if (counter > 1200)
                    {
                        MyMenu.windowClr();
                        break;
                    }
                    if (M5.BtnA.wasPressed())
                    {
                        break;
                    }
                }
                MyMenu.windowClr();
                MyMenu.drawAppMenu(F("WiFi"), F("ESC"), F("SELECT"), F("LIST"));
                MyMenu.showList();
            }
            if (MyMenu.getListString() == "WPS Pin Code")
            {
                MyMenu.windowClr();
                delay(200);
                Wps_run(false);
                while (!WiFi.isConnected())
                {
                    delay(50);
                    M5.update();
                    counter++;
                    if (counter > 2400)
                    {
                        MyMenu.windowClr();
                        break;
                    }
                    if (M5.BtnA.wasPressed())
                    {
                        break;
                    }
                }
                MyMenu.windowClr();
                MyMenu.drawAppMenu(F("WiFi"), F("ESC"), F("SELECT"), F("LIST"));
                MyMenu.showList();
            }
             if (MyMenu.getListString() == "WiFi OFF")
            {
                MyMenu.windowClr();
                delay(200);
                WiFi.disconnect();
                WiFi.mode(WIFI_MODE_NULL);
                while (!M5.BtnA.wasPressed())
                {
                    M5.update();
                }
                MyMenu.windowClr();
                MyMenu.drawAppMenu(F("WiFi"), F("ESC"), F("SELECT"), F("LIST"));
                MyMenu.showList();
            }
        }
        M5.update();
    }
    MyMenu.show();
}