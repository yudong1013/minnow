#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

bool Writer::is_closed() const
{
  // Your code here.
  return closed_ == true;
}

void Writer::push( string data )
{
  // Your code here.
  // // Push data to stream, but only as much as available capacity allows.
  const size_t len = min( data.size(), available_capacity() );
  if ( error_ || is_closed() || len == 0 ) {
    return;
  } else if ( len < data.size() ) {
    data.resize(len);
  }
  buffer_data.push( move( data ) );
  if ( buffer_data.size() == 1 ) {
    buffer_view = buffer_data.front();
  }
  bytes_pushed_ += len;
}

void Writer::close()
{
  // Your code here.
  closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_ + bytes_popped_ - bytes_pushed_;
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return bytes_pushed_;
}

bool Reader::is_finished() const
{
  // Your code here.
  return closed_ && bytes_buffered() == 0;
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return bytes_popped_;
}

string_view Reader::peek() const
{
  // Your code here.
  // Peek at the next bytes in the buffer
  return buffer_view;
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  // Remove `len` bytes from the buffer
  if ( error_ || len > bytes_buffered() || len == 0 ) {
    return;
  }
  // if (queue_.empty()) {
  //   return;
  // }
  bytes_popped_ += len;

  while ( len > 0 ) {
    if ( len >= buffer_view.size() ) {
      len -= buffer_view.size();
      buffer_data.pop();
      if ( buffer_data.empty() ) {
        buffer_view = string_view();
      } else {
        buffer_view = buffer_data.front();
      }
    } else {
      buffer_view.remove_prefix( len );
      len = 0;
    }
  }
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return bytes_pushed_ - bytes_popped_;
}
