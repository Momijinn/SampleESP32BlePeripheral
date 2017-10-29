#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#define TXRX_BUF_LEN 5
#define DEVICE_NAME  "MyESP32"
#define SERVICE_UUID         "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID  "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"

//Data
uint8_t tx_buf[TXRX_BUF_LEN];
//Characteristic
BLECharacteristic *pCharacteristic;

//Timer
volatile SemaphoreHandle_t timerSemaphore;


void IRAM_ATTR onTimer(){
    //print
    Serial.print("Send:");
    for(int i=0;i<TXRX_BUF_LEN;i++){
        tx_buf[i] += 1;
        Serial.print(tx_buf[i]);Serial.print(",");
    }
    Serial.println();

    //update notify
    pCharacteristic->setValue(tx_buf, TXRX_BUF_LEN); //send hex
    pCharacteristic->notify();

    xSemaphoreGiveFromISR(timerSemaphore, NULL);
  }


void setup() {
    Serial.begin(115200);

    // BLEデバイス名の定義
    BLEDevice::init(DEVICE_NAME);
    // BLEサーバーの定義
    BLEServer *pServer = BLEDevice::createServer();
    // BLEサービスの定義
    BLEService *pService = pServer->createService(SERVICE_UUID);
    // Characteristicの定義
    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_NOTIFY
                        );
    pCharacteristic->addDescriptor(new BLE2902());

    // Start
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();
    Serial.println("Waiting a client connection to notify...");


    //Timer
    timerSemaphore = xSemaphoreCreateBinary();
    hw_timer_t * timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000000, true); //1sec notify
    timerAlarmEnable(timer);

    //Initialize array
    for(int i=0;i<TXRX_BUF_LEN;i++){
        tx_buf[i] = 0;
    }
}

void loop() {
}