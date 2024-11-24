#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

class ResponseManager {
public:
	nlohmann::json get_places(std::string name_of_place, double lon, double lat) {
		this->responce = cpr::Get(cpr::Url{ "https://catalog.api.2gis.com/3.0/items?q=" + name_of_place + "&location=" + std::to_string(lon) + "," + std::to_string(lat) + "&key=" + this->key_2gis });
		if (this->responce.status_code != 200) {
			std::cout << this->responce.error.message << std::endl;
			return nullptr;
		}
		else {
			return nlohmann::json::parse(this->responce.text);
		}
	}

	nlohmann::json get_geocoder(std::string place) {
		this->responce = cpr::Get(cpr::Url{ ("https://catalog.api.2gis.com/3.0/items/geocode?q=" + place + "&fields=items.point&key=" + this->key_2gis) });
		if (this->responce.status_code != 200) {
			std::cout << this->responce.error.message << std::endl;
			return nullptr;
		}
		else {
			return nlohmann::json::parse(this->responce.text);
		}
	}
private:
	std::string key_2gis = "your_api_key";

	cpr::Response responce;
};