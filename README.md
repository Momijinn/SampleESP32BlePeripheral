# SampleESP32BlePeripheral
ESP32でPeripheralとしてBle通信をするサンプルプログラム

## 前提
ESP32をArduino上で動かしています

## 概要
ESP32をBLEのPeripheral化するプログラムを下記においておきます

Timerを使ってNotifyの更新を行っています


* BLEDevice::init();

    デバイス名の設定


* BLEServer *pServer = BLEDevice::createServer();

    Serverの設定

* pCharacteristic = pService->createCharacteristic();

* pCharacteristic->addDescriptor(new BLE2902());

    サービスの定義(Characteristic)

* pService->start();

    サーバーのスタート

* pServer->getAdvertising()->start();

    アドバタイジングのスタート

## blog
[AutumnColor.com](http://www.autumn-color.com)