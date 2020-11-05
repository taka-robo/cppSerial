//
// Created by taka on 2020/11/05.
//

#include "SerialCOM.hpp"

SerialCOM::SerialCOM(std::string device) {
  device_ = device;
  port_ = new boost::asio::serial_port(io_);
}

SerialCOM::~SerialCOM() {
  Close();
}
bool SerialCOM::Open() {
  isOpened_ = false;
  boost::system::error_code ret;
  port_->open(device_,ret);
  if( ret ) {
    std::string error_message = ret.message();
    spdlog::error("serial_port::open() Error ="+error_message);
  }
  else {
    spdlog::info("serial_port::open() Success = {}",device_);
    isOpened_ = true;
  }
  return isOpened_;
}
bool SerialCOM::Close() {
  boost::system::error_code ret;
  port_->close(ret);
  if( ret ) {
    std::string error_message = ret.message();
    spdlog::error("serial_port::open() Error ="+error_message);
    return false;
  }
  else {
    isOpened_ = false;
  }
  return true;
}
void SerialCOM::SetOption() {
  // TODO:シリアルポートの設定を変更できるようにする
  port_->set_option(boost::asio::serial_port_base::baud_rate(115200));
  port_->set_option(boost::asio::serial_port_base::character_size(8));
  port_->set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
  port_->set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
  port_->set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
}
void SerialCOM::read_callback(const boost::system::error_code &e, std::size_t size)
{
  std::cout.write(buf_.data(), size);
  port_->async_read_some( boost::asio::buffer(buf_), boost::bind(&SerialCOM::read_callback,this,boost::placeholders::_1,boost::placeholders::_2));
}
void SerialCOM::StartRead() {
  if(isOpened()==false){
    spdlog::error("serial port is not open");
  }
  boost::thread thr_io(boost::bind(&boost::asio::io_service::run, &io_));
  port_->async_read_some( boost::asio::buffer(buf_), boost::bind(&SerialCOM::read_callback,this,boost::placeholders::_1,boost::placeholders::_2));
}
bool SerialCOM::isOpened() {
  return isOpened_;
}
