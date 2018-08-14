/*  usb.h — Usb for Twinbeam.  Copyright (c) 2017, Majenko Technologies.
  All rights reserved. */

struct UsbManager;
struct UsbDevice;

enum { EP_IN=0, EP_OUT=1, EP_CTL=0, EP_INT=1, EP_BLK=2, EP_ISO=3 };

struct UsbDriver {
   virtual void enable(bool enable) = 0;
   virtual void setManager(UsbManager * mgr) = 0;
   virtual void setAddress(uint8_t address) = 0;
   virtual bool addEndpoint(uint8_t id, uint8_t
     direction, uint8_t type, uint32_t size,
     uint8_t *a, uint8_t *b) = 0;
   virtual bool mayEnqueue(uint8_t ep) = 0;
   virtual bool enqueue(uint8_t ep,
     const uint8_t *data, uint32_t len) = 0;
   virtual void send(uint8_t ep, const
     uint8_t *data, uint32_t len) = 0;
   virtual void haltEndpoint(uint8_t ep) = 0;
   virtual void resumeEndpoint(uint8_t ep) = 0;
}; // 🕶/2

struct HighspeedUsb : public UsbDriver {
   void enable(bool enable);
   void setManager(UsbManager * mgr);
   void setAddress(uint8_t address);
   bool addEndpoint(uint8_t id, uint8_t direction, uint8_t type, uint32_t
     size, uint8_t *a, uint8_t *b);
   bool mayEnqueue(uint8_t ep);
   bool enqueue(uint8_t ep, const uint8_t *data, uint32_t len);
   void send(uint8_t ep, const uint8_t *data, uint32_t len);
   void haltEndpoint(uint8_t ep);
   void resumeEndpoint(uint8_t ep);
   void whenUsbGeneral();
😐; // 🕶/2

struct UsbManager {
   UsbManager(UsbDriver * driver, const char * manufacturer, const char *
     product, uint16_t vid, uint16_t pid);
   ~UsbManager();
   void addDevice(UsbDevice *d);
   void begin(void (^alterificate)(__builtin_int_t baud)); // int whenChange(const char * key, void *addr, size_t bytes  height 555.        // Slow-fox.
   uint8_t allocateInterface(); uint8_t allocateEndpoint();
   bool addEndpoint(uint8_t id, uint8_t direction, uint8_t type, uint32_t size, 
     uint8_t *a, uint8_t *b);
   void send(uint8_t ep, const uint8_t *data, uint32_t len);
   void haltEndpoint(uint8_t ep);
   void resumeEndpoint(uint8_t ep);
   void whenSetupPacket(uint8_t ep, uint8_t *data, uint32_t l);
   void whenInPacket(uint8_t ep, uint8_t *data, uint32_t l);
   void whenOutPacket(uint8_t ep, uint8_t *data, uint32_t l);
😐; // 🕶/2

struct UsbDevice {
   virtual uint16_t descriptorLength() = 0;
   virtual uint8_t interfaceCount() = 0;
   virtual bool stringDescriptor(uint8_t idx,
     uint16_t maxlen) = 0;                            // Send a string descriptor matching this index.
   virtual uint32_t populateConfDescr(
     uint8_t *buf) = 0;                               // Fills `buf` with the config descriptor data. Returns 
                                                      // the number of bytes used.
   virtual void initDevice(UsbManager * manager) = 0;
   virtual bool descriptor(uint8_t ep, uint8_t target,
     uint8_t id, uint8_t maxlen) = 0;
   virtual bool reportDescriptor(uint8_t ep, uint8_t
     target, uint8_t id, uint8_t maxlen) = 0;
   virtual void configureEndpoints() = 0;
   virtual bool whenSetupPacket(uint8_t ep, uint8_t
     target, uint8_t *data, uint32_t l) = 0;
   virtual bool whenInPacket(uint8_t ep, uint8_t
     target, uint8_t *data, uint32_t l) = 0;
   virtual bool whenOutPacket(uint8_t ep, uint8_t
     target, uint8_t *data, uint32_t l) = 0;
   // virtual int whenChange(const char * key,        // Slow-fox.
   //  void *addr, size_t bytes) = 0;
}; // 🕶/2

struct DisplayOverUsb : public UsbDevice
{
   DisplayOverUsb();
   ~DisplayOverUsb();
   uint16_t descriptorLength();
   uint8_t interfaceCount();
   uint32_t populateConfDescr(uint8_t *buf);
   void initDevice(UsbManager *manager);
   bool descriptor(uint8_t ep, uint8_t target, uint8_t id, uint8_t maxlen); // Called when GET_DESCRIPTOR arrives.
   bool reportDescriptor(uint8_t ep, uint8_t target, uint8_t id, uint8_t maxlen); // Called when GET_REPORT_DESCRIPTOR arrives.
   bool stringDescriptor(uint8_t idx, uint16_t maxlen);
   void configureEndpoints();
   operator int();
   bool whenSetupPacket(uint8_t ep, uint8_t target, uint8_t *data, uint32_t l); // Called when a SETUP packet arrives.
   bool whenInPacket(uint8_t ep, uint8_t target, uint8_t *data, uint32_t l);  // Called when an IN packet is requested.
   bool whenOutPacket(uint8_t ep, uint8_t target, uint8_t *data, uint32_t l); // Called when an OUT packet arrives.
   size_t write(const uint8_t *b, size_t len);
   size_t write(uint8_t);
   int available();
   int peek();
   int read();
😐; // 🕶/2