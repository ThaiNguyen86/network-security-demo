Cài đặt thư viên OpenSSL từ trang web https://slproweb.com/products/Win32OpenSSL.html
Để chạy http_server:
Chuột phải vào project http_server chọn properties
Ở Configuration Properties thẻ General C++ language standard chọn phiên bản C++ 20
Ở VC++ Directories chỉnh sửa Include Directories thành đường dẫn đến file network-security-demo/include
Để chạy https_server:
Chuột phải vào project https_server chọn properties
Ở Configuration Properties thẻ General C++ language standard chọn phiên bản C++ 20
Thẻ Debugging thay Working directory thành đường dẫn đến thư mục network-security-demo
Ở VC++ Directories chỉnh sửa Include Directories thành đường dẫn đến file network-security-demo/include và đường dẫn đến file include của thư viện OPENSSL thường là C:\Program Files\OpenSSL-Win64\include
Ở Library Directories thay thành đường dẫn đến file thư viện của OPENSSL thường là C:\Program Files\OpenSSL-Win64\lib
Ở thẻ Linker General -> Additional Library Directories thêm đường dẫn đến 2 file thư viện libcrypto.lib và libssl.lib thường là C:\Program Files\OpenSSL-Win64\lib\VC\x64\MD; và file kernel32.Lib thường là C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x64;$(VC_LibraryPath_x64);$(WindowsSdkLibPath)
Ở Input thay thành libssl.lib;libcrypto.lib;%(AdditionalDependencies)