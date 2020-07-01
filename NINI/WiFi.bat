@echo off
:work
	netstat -r | findstr /C:"Microsoft Virtual WiFi Miniport Adapter" && (netsh wlan set hostednetwork mode=disallow && netsh wlan STOP hostednetwork) || (netsh wlan set hostednetwork mode=allow && netsh wlan start hostednetwork)
	::netsh wlan set hostednetwork mode=allow ssid=ABacker_wifi key=654321789
:end
	pause