![icon](https://github.com/maladi17/kartego/blob/master/IMG_20200828_015910.jpg)
# kartego

A light version of scapy in c  I quickly made during a penetration test.  for windows only.

## Getting Started


### Prerequisites

the winpcap library should be installed in the project.
try these manuals:
      https://www.winpcap.org/docs/docs_412/html/group__compilation.html
      
  or 
  
  
  
 https://youtu.be/YpnrR7D_lRI       (it's not a fishing...just search for C++ & PCAP Files made by NYUCyFor in youtube =])
      
  
  
### Installing

1.  download the code from the repo.
2.  pay attention to the packet.txt file. put your data in there and don't forget to put a blank line in the end of the file.
3.  compile the code.

** pay attention to the dissector i have added to the repo in oder to sniff the packet.

### Usage

the following is the main menu:

![main menu](https://github.com/maladi17/kartego/blob/master/man.PNG)

in order to send a pcap,just set a wanted pcap size (if the data you have given is smaller than the size,it will randomize the rest of data). and then use the send command:

![send](https://github.com/maladi17/kartego/blob/master/send.JPG)

this is the wireshark look (without the appropriate dissector). pay attention I have created a bogus packet by intention...

![send](https://github.com/maladi17/kartego/blob/master/pcap.JPG)

### important notes
- the packet data should be in a txt file in a folder of your choice. a byte per a line in hex (I know...yak)
 - you currently cannot  insert a file which is both commented and a hex stream.

### Updates

- [x] support to files contains comments (only // for now and in the same line of the hex. Check out our packet.txt example.

- [x] support in sending packets from wireshark to the wire based on hexstream file.
Checkout our wireshark_pkt.txt file.
>> in wireshark select Copy->Bytes->Hex stream, you'll get the hex digits as one long string without white spaces.
![filter](https://github.com/maladi17/kartego/blob/master/wireshark_filter.jpg)
 By the way, you can send an accurate packet size using this:
![size of packet](https://github.com/maladi17/kartego/blob/master/size.JPG)

- [x] support in sending 1-30 packets types in a raw.

- [x] support in sending a pkt with a delay and replay it.

- [x] support of the above features with conf file mode.

- [x] support in fields increment during a couple of times sending.
By giving the bytes number as follow:
![columns](https://github.com/maladi17/kartego/blob/master/description_fields.JPG)
Pay attention that given the vals from=x, to=y in the conf file, it will change bytes x to y (without y).

## Authors

* **maladi17**- I am really busy, but open for suggestions to improve the repo or bug fixing. just open an issue or leave a mail and I will do my best to improve it.
