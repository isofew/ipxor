CXXFLAGS+= -std=c++11
LDFLAGS+= -lnetfilter_queue -ltins -lpcap

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

ipxor: ipxor.o nfq.o
	$(CXX) -o ipxor *.o $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f *.o ipxor
