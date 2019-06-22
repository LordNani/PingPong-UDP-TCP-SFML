#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <math.h>
#include <vector>

enum Nodemode : char { SERVER = 's', CLIENT = 'c' };
sf::IpAddress hostIp = sf::IpAddress::getLocalAddress();
sf::UdpSocket udpSocket;
uint16_t port = 51234;
std::string recMsg = "";
std::string msg;

std::istream &operator>>(std::istream &is, Nodemode &i);
std::ostream &operator<<(std::ostream &out, const Nodemode value);

void sendData(std::string msg);
Nodemode nodestate;
sf::Thread secondThread(&sendData, msg);

int main() {

  std::cout << "Type 's' for server, and 'c' for client. If you want to close "
               "the app, type in 'stop' "
            << std::endl;
  std::cin >> nodestate;

  if (nodestate == SERVER) {
	  udpSocket.bind(port);
  } else if (nodestate == CLIENT) {
	  udpSocket.bind(port);
  }

  std::cout << "Current IP-address: " << hostIp.toString() << std::endl;
  std::cout << "Node state: " << nodestate << std::endl;
  std::cout << recMsg << std::endl;

  secondThread.launch();
  while (msg != "stop") {

    sf::Packet packet2;
	if (udpSocket.receive(packet2, hostIp, port) != sf::Socket::Done)
		std::cout << "~~error receiving data" << std::endl;
	else {
		std::cout << "--data received" << std::endl;
		packet2 >> recMsg;
		if (recMsg != "")
			std::cout << "Other user: " << recMsg << std::endl;
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

std::ostream &operator<<(std::ostream &out, const Nodemode value) {
  static std::map<Nodemode, std::string> strings;
  if (strings.size() == 0) {
#define INSERT_ELEMENT(p) strings[p] = #p
    INSERT_ELEMENT(SERVER);
    INSERT_ELEMENT(CLIENT);
#undef INSERT_ELEMENT
  }
  return out << strings[value];
}

void sendData(std::string msg) {
  while (msg != "stop") {

    getline(std::cin, msg);
    sf::Packet packet;
    packet << msg;

	if (udpSocket.send(packet, hostIp, port) != sf::Socket::Done)
		std::cout << "~~Could not send data" << std::endl;
  }
}
