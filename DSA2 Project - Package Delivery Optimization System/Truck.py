class Truck:
    #Constructor
    def __init__(self, package_ids, departure_time, truck_id, max_capacity=16, travel_speed=18, total_mileage=0.0, current_address="4001 South 700 East"):
        self.max_capacity = max_capacity
        self.travel_speed = travel_speed
        self.current_load = 0
        self.packages = package_ids
        self.mileage = total_mileage
        self.address = current_address
        self.depart_time = departure_time
        self.time = departure_time
        self.truck_id = truck_id