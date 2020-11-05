//
// Created by taka on 2020/11/05.
//
/**
 * @file SimulatorCOM.hpp
 * @brief マイコンとシリアル通信するためのオブジェクト
 **/

#ifndef SERIAL_TEST_SERIALCOM_HPP
#define SERIAL_TEST_SERIALCOM_HPP

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include "spdlog/spdlog.h"

/**
 * @brief マイコンと通信するためクラス
 **/
class SerialCOM {
public:
  /**
  * @brief コンストラクタ
  * @param device 接続するデバイスのPort
  **/
  SerialCOM(std::string device);
  /**
  * @brief デストラクタ
  **/
  virtual ~SerialCOM();
  /**
  * @brief ポートをオープン
  **/
  bool Open();
  /**
  * @brief ポートをクローズ
  **/
  bool Close();
  /**
  * @brief ポートの設定
  **/
  void SetOption();
  /**
  * @brief 非同期受信をスタート
  **/
  void StartRead();
  /**
  * @brief Portをオープンしたか?
  * @return true:接続済み false:未接続
  * @note 必ずしも現在の接続状況を示すものではない
  **/
  bool isOpened();
  void read_callback(const boost::system::error_code& e, std::size_t size);

private:
  boost::asio::io_service io_;
  boost::asio::serial_port* port_;
  std::string device_;
  bool isOpened_;
  boost::array<char, 64> buf_;
};


#endif //SERIAL_TEST_SERIALCOM_HPP
