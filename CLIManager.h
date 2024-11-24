#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "ResponseManager.h"

class CLIManager {
public:
	CLIManager()
	{
		std::shared_ptr<ResponseManager> a_manager = std::make_shared<ResponseManager>();
	}

	void run() {
		std::string choise;
		while (true) {
			std::cout << "1 - Get places by lon and lat" << std::endl
				<< "2 - Get geocoder by address" << std::endl
				<< "Else - Exit" << std::endl;
			std::cin >> choise;
			if (choise == "1") {
				places();
			}
			else if (choise == "2") {
				geocoder();
			}
			else {
				break;
			}
		}
	}

	void places() {
		std::string place;
		double lon, lat;
		std::cout << "Enter the title of place(in russian): ";
		std::getline(std::cin, place);
		std::cout << "Enter the lon: ";
		std::cin >> lon;
		std::cout << "Enter the lat: ";
		std::cin >> lat;
		nlohmann::json places = r_manager->get_places(place, lon, lat);
		std::cout << places;
		for (auto i : places["result"]["items"]) {
			std::cout << "Name: " + i["name"] << std::endl
				<< "ID: " + i["id"] << std::endl
				<< "Address name: " + i["address_name"] << std::endl
				<< "Address coment: " + i["address_comment"] << std::endl
				<< "Type: " + i["type"] << std::endl;
		}
	}

	void geocoder() {
		std::string place;
		std::cout << "Enter the title of address: ";
		std::getline(std::cin, place);
		nlohmann::json places = r_manager->get_geocoder(place);
		std::cout << places;
		for (int i :places["result"]["total"]) {
			std::cout << "Full name: " + i["full_name"] << std::endl
				<< "ID: " + i["id"] << std::endl
				<< "Lat: " + i["point"]["lat"] << std::endl
				<< "Lon: " + i["point"]["lon"] << std::endl
				<< "Purpose name: " + i["purpose_name"] << std::endl
				<< "Type: " + i["type"] << std::endl;
		}
	}
private:
	std::shared_ptr<ResponseManager> r_manager = std::make_shared<ResponseManager>();
};