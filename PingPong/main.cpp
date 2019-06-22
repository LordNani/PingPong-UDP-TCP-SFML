#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <math.h>
#include <vector>

enum Nodemode : char { SERVER = 's', CLIENT = 'c' };

// sf::RenderWindow window(sf::VideoMode(800, 600), "ping?pong!",
//                        sf::Style::Default);
// sf::IpAddress hostIp = sf::IpAddress("25.63.232.166");
sf::IpAddress hostIp = sf::IpAddress::getLocalAddress();
sf::TcpSocket tcpSocket;
uint16_t port = 66000;
std::size_t received;
std::string recMsg = "Connection established SUCCESFULLY";
std::string msg;
std::istream &operator>>(std::istream &is, Nodemode &i);
std::ostream &operator<<(std::ostream &out, const Nodemode value);
void sendData(std::string msg);
sf::Thread secondThread(&sendData, msg);
Nodemode nodestate;
// void pause();
// bool paused = false;

int main() {

  std::cout << "Type 's' for server, and 'c' for client. If you want to close "
               "the app, type in 'stop' "
            << std::endl;
  std::cin >> nodestate;
  if (nodestate == SERVER) {
    sf::TcpListener listener;
    listener.listen(port);
    listener.accept(tcpSocket);
  } else if (nodestate == CLIENT) {
    tcpSocket.connect(hostIp, port);
	  port;
  }

  std::cout << "Current IP-address: " << hostIp.toString() << std::endl;
  std::cout << "Node state: " << nodestate << std::endl;
  std::cout << recMsg << std::endl;
  secondThread.launch();
  while (msg != "stop") {

    sf::Packet packet2;
    if (tcpSocket.receive(packet2) != sf::Socket::NotReady) {
      packet2 >> recMsg;
      if (recMsg != "")
        std::cout << "Other user: " << recMsg << std::endl;
    }
  }
  /* while (window.isOpen()) {
     sf::Event event;
     while (window.pollEvent(event)) {
       switch (event.type) {
       case sf::Event::Closed:
         window.close();
         break;
       case sf::Event::LostFocus:
         pause();
         break;
       }
     }
         window.clear(sf::Color::Black);
         window.display();

   } */
  return 0;
}

// void pause() {
//	while(paused){
//		sf::Event event;
//		while (window.pollEvent(event)) {
//			if(event.type ==  sf::Event::GainedFocus){
//				paused = false;
//			}
//		}
//	}
//}

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

    tcpSocket.send(packet);

  }
}
