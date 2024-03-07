#include <iostream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
    cout << "\t +-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-+" << endl;
    cout << "\t\tMy weather app" << endl;
    cout << "\t +-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-+" << endl;
    cout << "\tEnter city name: ";
    string city;
    getline(cin, city);

    http_client client(U("https://api.openweathermap.org/data/2.5/weather?q=&appid=fa3884882d04fc81534b02dbab4307fd"));
    uri_builder builder(U("/weather"));
    builder.append_query(U("q"), utility::conversions::to_string_t(city));
    builder.append_query(U("appid"), U("fa3884882d04fc81534b02dbab4307fd")); // Fixed typo here
    http_request request(methods::GET);
    request.set_request_uri(builder.to_string());

    client.request(request).then([](http_response response) {
        return response.extract_json();
        }).then([](web::json::value body) {
            cout << "\tTemperature: " << body[U("main")][U("temp")].as_double() << " k" << endl;
            cout << "\thumidity: " << body[U("main")][U("humidity")].as_double() << " %" << endl;
            cout << "\tweather: " << utility::conversions::to_utf8string(body[U("weather")][0][U("main")].as_string()) << endl; // Fixed missing closing parenthesis
            }).wait();

            return 0;
}
