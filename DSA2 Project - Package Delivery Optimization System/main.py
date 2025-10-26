'''
Name: Kamren Northrop
Student ID: 011338614 
'''
import csv
import re
from datetime import timedelta
from Truck import Truck
from HashTable import HashTable
from Package import Package

#Read distances and address' from csv files
with open("./distances.csv") as distance_file, open("./addresses.csv") as address_file:
    distances = list(csv.reader(distance_file))
    addresses = list(csv.reader(address_file))

#Read package info from csv and insert it into the hash table
with open("./packages.csv") as package_file:
    package_table = HashTable()

    for row in csv.reader(package_file):
        package_id = int(row[0])
        note = row[7] if len(row) > 7 else ""

        #Identify package dependencies from the note, if any
        text_match = re.search(r"must be delivered with (.*)", note)
        if text_match:
            dependencies = [int(depen.strip()) for depen in text_match.group(1).split(",")]
        else:
            dependencies = []

        #Check for delayed packages
        delay_time = timedelta(hours=9, minutes=5) if "delayed on flight" in note else None

        #Create a package object and store it in the hash table
        package = Package(package_id, row[1], row[2], row[3], row[4], row[5], row[6], "at the hub", dependencies, delay_time)
        
        # Assign truck_id based on package_id
        #10:30am deliveries, and packages with dependencies (must be with delivered with) truck 1 
        #Can only be on truck 2 packages, flight delays arriving at 9:05 truck 2
        #remaining EOD deliveries, and package 9 to compensate for late address fix truck 3. 
        if package_id in [1, 2, 4, 5, 13, 14, 15, 16, 19, 20, 29, 30, 31, 34, 37, 40]:
            package.truck_id = 1
        elif package_id in [3, 6, 18, 25, 28, 32, 36, 38]:
            package.truck_id = 2
        elif package_id in [7, 8, 9, 10, 11, 12, 17, 21, 22, 23, 24, 26, 27, 33, 35, 39]:
            package.truck_id = 3

        package_table.insert(package_id, package)

#Define the fleet of trucks and assign packages with departure times
#Truck 1: 10:30am deliveries, and packages with dependencies (must be with delivered with) -- last package delivered at 9:42am
#Truck 2: Can only be on truck 2 packages, flight delays arriving at 9:05
#Truck 3: remaining EOD deliveries, and package 9 to compensate for late address fix -- Package starts delivering at 10:20am
truck_one = Truck([1, 2, 4, 5, 13, 14, 15, 16, 19, 20, 29, 30, 31, 34, 37, 40], timedelta(hours=8), 1)
truck_two = Truck([3, 6, 18, 25, 28, 32, 36, 38], timedelta(hours=9, minutes=5), 2)
truck_three = Truck([7, 8, 9, 10, 11, 12, 17, 21, 22, 23, 24, 26, 27, 33, 35, 39], timedelta(hours=10, minutes=20), 3)

truck_fleet = [truck_one, truck_two, truck_three]

#Calculate the distance between two addresses using the address indices
def calculate_distance(address1_index, address2_index):
    distance = distances[address1_index][address2_index] or distances[address2_index][address1_index]
    return float(distance)

#Find the index of an address in the addresses list
def get_address_index(address):
    for row in addresses:
        if address in row[2]:
            return int(row[0])
        
    return None

#Optimize the delivery route for a truck -- Greedy Algorithm
'''
This greedy algorithm creates a list of undelivered packages from the packages currently on the truck and clears the truck's package list.
Then, it iterates through the undelivered packages list to determine which package is the nearest to the truck's current address.
Once the nearest package is found, it is added back onto the truck's package list in order of closest to farthest, 
removed from the undelivered list, and the truck's mileage, address, time, delivery time, and departure time are updated accordingly.
'''

def optimize_route(truck):
    undelivered_packages = [package_table.lookup(package_id) for package_id in truck.packages]
    truck.packages.clear()

    while undelivered_packages:
        nearest_package = None
        shortest_distance = float('inf')

        #Skip packages delayed if it's after the truck's current time
        for package in undelivered_packages:
            if package.delay_time and package.delay_time > truck.time:
                continue
            distance = calculate_distance(get_address_index(truck.address), get_address_index(package.address))

            #Identify if the calculated distance is less than the current known shortest distance
            if distance < shortest_distance:
                shortest_distance = distance
                nearest_package = package

        #If it is, put on truck and update calculated info
        if nearest_package:
            truck.packages.append(nearest_package.package_id)
            undelivered_packages.remove(nearest_package)
            truck.mileage += shortest_distance
            truck.address = nearest_package.address
            truck.time += timedelta(hours=shortest_distance / truck.travel_speed)
            nearest_package.delivery_time = truck.time
            nearest_package.departure_time = truck.depart_time

#Optimize routes for all the trucks
optimize_route(truck_one)
optimize_route(truck_two)
optimize_route(truck_three)

#Main Program
class Main:
    #Constructor
    def __init__(self):
        print("Welcome to the WGUPS Parcel Service")
        self.main_menu()

    #Report for a single package
    def display_single_package_report(self):
        try:
            package_id = int(input("Package ID? (1-40) "))
            if 1 <= package_id <= 40:
                user_input = input("At What Time? (HH:MM AM/PM) ").strip()

                #Separating the time(HH:MM) from the time of day (AM/PM), extracting hours / minutes using regular expression
                if " " in user_input:
                    hour = None
                    time, time_of_day = user_input.rsplit(" ", 1)

                    time_to_extract = re.match(r"(\d{1,2}):(\d{2})", time)

                    valid = ["AM", "PM", "am", "pm", "aM", "pM", "Am", "Pm"]
                    if time_of_day not in valid:
                        print("Please Enter A Valid Time Of Day.")
                        return self.display_single_package_report()

                    if time_to_extract: 
                        hour = int(time_to_extract.group(1))
                        minute = int(time_to_extract.group(2))
                    else:
                        print("Input Error. Please Follow The Specified Format.")
                        return self.display_single_package_report()

                    #Determining if it's morning or night by converting 12-hour times to 24-hour times
                    if time_of_day.lower() == "pm" and hour != 12:
                        hour += 12
                    elif time_of_day.lower() == "am" and hour == 12:
                        hour = 0
                    selected_time = timedelta(hours=hour, minutes=minute)
                else:
                    print("Input Error. Please Follow The Specified Format.")
                    return self.display_single_package_report()
                
                #Finding the package
                package = package_table.lookup(package_id)
                if package:
                    print(f"\n-----Report For Package ID: {package_id}, at {time} {time_of_day.upper()}-----")
                    print(package.update_status(selected_time))
                else:
                    print("Package ID Not Found.")
            else:
                print("Please Enter An ID Between 1 and 40.")
                self.display_single_package_report()
        except ValueError:
            print("Input Error. Please Follow The Specified Format.")
            self.display_single_package_report()

    #Report information for all packages report
    def display_all_package_report_info(self):
        try:
            user_input = input("At What Specified Time? (HH:MM AM/PM) ").strip()

            #separating the time(HH:MM) from the time of day (AM/PM), extracting hours / minutes using regular expression -- (Hour(digit 1 or 2 digit occurence), minute(2 digit occurence))
            if " " in user_input:
                time, time_of_day = user_input.rsplit(" ", 1)
                
                time_to_extract = re.match(r"(\d{1,2}):(\d{2})", time)
                if time_to_extract: 
                    hour = int(time_to_extract.group(1))
                    minute = int(time_to_extract.group(2))

                    valid = ["AM", "PM", "am", "pm", "aM", "pM", "Am", "Pm"]
                    if time_of_day not in valid:
                        print("Please Enter A Valid Time Of Day.")
                        return self.display_all_package_report_info()
                else:
                    print("Input Error. Please Follow The Specified Format.")
                    return self.display_all_package_report_info()

                #Determining if it's morning or night by converting 12-hour times to 24-hour times
                if time_of_day.lower() == "pm" and hour != 12:
                    hour += 12
                elif time_of_day.lower() == "am" and hour == 12:
                    hour = 0
                selected_time = timedelta(hours=hour, minutes=minute)
            else:
                print("Input Error. Please Follow The Specified Format.")
                return self.display_all_package_report_info()
            
            #Displaying the packages
            self.display_all_packages(selected_time)
        except ValueError:
            print("Input Error. Please Follow The Specified Format.")
            return self.display_all_package_report_info()

    #Helper function to display all the packages at a specificed time
    def display_all_packages(self, specified_time):
        #specified conversion getting total seconds, into military hours, into minutes
        total_seconds = specified_time.total_seconds()
        military_hours = int(total_seconds // 3600)
        minutes = int((total_seconds % 3600) // 60)

        #Determining AM/PM time of day and converting the 24-hour military time to 12-hour standard time
        time_of_day = "AM" if military_hours < 12 else "PM"
        standard_hours = military_hours % 12
        if standard_hours == 0:
            standard_hours = 12

        print(f"----------Package Report {standard_hours:02}:{minutes:02} {time_of_day}----------")

        #Looking up the package id, and updating its status
        for package_id in range(1, 41):
            package = package_table.lookup(package_id)

            if package:
                for truck in truck_fleet:
                    if package_id in truck.packages:
                        print(f"Package {package.update_status(specified_time)}")
                        break

        self.display_total_mileage(specified_time)
    
    #Calculate distance traveled based on specified time
    #Ignore packages if it's time is after the specified time.
    def calculate_mileage_by_time(self, truck, specified_time):
        #Initializations
        mileage_by_time = 0.0
        current_time = truck.depart_time
        current_address = truck.address

        #Looping through each package on the truck, and looking it up
        for package_id in truck.packages:
            package = package_table.lookup(package_id)

            #Calculating distance if package delivery time is within the specified time
            if package.delivery_time and package.delivery_time <= specified_time:
                distance = calculate_distance(get_address_index(current_address), get_address_index(package.address))
                mileage_by_time += distance
                current_address = package.address
                current_time = package.delivery_time
            else:
                break 

        return mileage_by_time

    #Display the total miles traveled of each truck
    def display_total_mileage(self, specified_time=None):
        total_distance = 0.0

        #calculating and displaying truck 1's miles
        print(f"\nTruck 1 current total miles at {specified_time}: {self.calculate_mileage_by_time(truck_one, specified_time):.2f} miles")
        total_distance += self.calculate_mileage_by_time(truck_one, specified_time)

        #calculating and displaying truck 2's miles
        if specified_time >= truck_two.depart_time:
            print(f"Truck 2 current total miles at {specified_time}: {self.calculate_mileage_by_time(truck_two, specified_time):.2f} miles")
            total_distance += self.calculate_mileage_by_time(truck_two, specified_time)
        else:
            print(f"Truck 2 current total miles at {specified_time}: 0.00 miles")

        #calculating and displaying truck 3's miles
        if specified_time >= truck_three.depart_time:
            print(f"Truck 3 current total miles at {specified_time}: {self.calculate_mileage_by_time(truck_three, specified_time):.2f} miles")
            total_distance += self.calculate_mileage_by_time(truck_three, specified_time)
        else:
            print(f"Truck 3 current total miles at {specified_time}: 0.00 miles")

        #Converting and formating specified time
        if specified_time:
            total_seconds = specified_time.total_seconds()
            hours = int(total_seconds // 3600)
            minutes = int((total_seconds % 3600) // 60)
            time_of_day = "AM" if hours < 12 else "PM"
            hours = hours % 12 or 12
            time_str = f"{hours:02}:{minutes:02} {time_of_day}"
        else:
            time_str = "now"

        print(f"\nTotal Miles Traveled By All Trucks {time_str} Is {total_distance:.2f} Miles")

    #Main Menu
    def main_menu(self):
        #Initialize to running state
        Running = True

        while Running:
            print("Enter 'A' All Package Report ")
            print("Enter 'B' Single Package Report ")
            print("Enter 'C' Exit Program ")

            #Get user input and convert to uppercase
            user_input = input("").upper()

            #Handling user input
            if user_input == "A":
                self.display_all_package_report_info()
            elif user_input == "B":
                self.display_single_package_report()
            elif user_input == "C":
                Running = False
                exit()
            else:
                print("Please Select One Of The Listed Options")

#Executing main
if __name__ == "__main__":
    Main()
