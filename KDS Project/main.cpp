#include "mbed.h"
#include "EthernetInterface.h"
#include "HTTP/HTTPClient.h"

EthernetInterface eth;
HTTPClient http;
DigitalOut red(LED_RED);
DigitalIn btn3(SW3);

char str[512];

int main()
{
	int ret = 1;
	bool AlreadySent = false;
	HTTPMap map;
	HTTPText inText(str, 512);

    eth.init("192.168.1.102", "255.255.255.0", "192.168.1.101");
    eth.connect();
    
    while(true)
    {
		if(btn3 && !AlreadySent)
		{
			ret = http.post("http://192.168.1.101:8000/index.php", map, &inText);
			AlreadySent = true;
		}
		else if(!btn3)
		{
			AlreadySent = false;
		}
    }
    eth.disconnect();
}
