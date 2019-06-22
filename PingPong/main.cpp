#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
enum Nodemode : char { SERVER = 's', CLIENT = 'c' };
sf::IpAddress hostIp = sf::IpAddress("25.63.232.166");
sf::IpAddress clientIp = sf::IpAddress("25.64.235.153");
sf::UdpSocket udpSocket;
unsigned short port = 51234;
string recMsg = "UDP-BASED CONNECTION ESTABLISHED";
string msg;
istream &operator>>(istream &is, Nodemode &i);
ostream &operator<<(ostream &out, const Nodemode value);
void sendData(string msg);
Nodemode nodestate;
sf::Thread secondThread(&sendData, msg);
sf::Packet packet2;
sf::Packet packet;

int main() {
  cout << "Type 's' for server, and 'c' for client. If you want to close "
          "the app, type in 'stop' "
       << endl;
  cin >> nodestate;

  if (nodestate == SERVER) {
	  
  } else if (nodestate == CLIENT) {
  }

  udpSocket.bind(port);

  cout << "IP-address: " << hostIp.toString() << endl;
  cout << "Port: " << port << endl;
  cout << "Node state: " << nodestate << endl;


  secondThread.launch();
  
  while (msg != "stop") {
	  sf::IpAddress tempIp = hostIp;
	  sf::IpAddress tempIp2 = clientIp;
	  unsigned short tempPort = port;
	  if (nodestate == SERVER) {
		  if (udpSocket.receive(packet2, tempIp2, tempPort) != sf::Socket::Done)
			  cout << "~~error receiving data" << endl;
		  else {
			  cout << "--data received" << endl;
			  packet2 >> recMsg;
			  if (recMsg != "")
				  cout << "Other user: " << recMsg << endl;
		  }
	  }	else   if (nodestate == CLIENT) {
		  if (udpSocket.receive(packet2, tempIp, tempPort) != sf::Socket::Done)
			  cout << "~~error receiving data" << endl;
		  else {
			  cout << "--data received" << endl;
			  packet2 >> recMsg;
			  if (recMsg != "")
				  cout << "Other user: " << recMsg << endl;
		  }
	  }
  }
  return 0;
}

std::istream &operator>>(std::istream &is, Nodemode &i) {
  char tmp;
  if (is >> tmp)
    i = static_cast<Nodemode>(tmp);
  return is;
}

ostream &operator<<(ostream &out, const Nodemode value) {
  static map<Nodemode, string> strings;
  if (strings.size() == 0) {
#define INSERT_ELEMENT(p) strings[p] = #p
    INSERT_ELEMENT(SERVER);
    INSERT_ELEMENT(CLIENT);
#undef INSERT_ELEMENT
  }
  return out << strings[value];
}

void sendData(string msg) {

  while (msg != "stop") {
    getline(std::cin, msg);
	if (msg == "info") {
		cout << "IP-address: " << hostIp.toString() << endl;
		cout << "Port: " << port << endl;
	}
    sf::Packet packet;
    packet << msg;
	if (nodestate == SERVER) {
		if (udpSocket.send(packet, clientIp, port) != sf::Socket::Done)
			std::cout << "~~Could not send data" << std::endl;
		else
			cout << "--Data sent" << endl;
	}else 	if (nodestate == CLIENT) {
		if (udpSocket.send(packet, hostIp, port) != sf::Socket::Done)
			std::cout << "~~Could not send data" << std::endl;
		else
			cout << "--Data sent" << endl;
	}
  }
}
