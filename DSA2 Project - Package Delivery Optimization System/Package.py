from datetime import timedelta
from Truck import Truck

class Package:
    #Constructor
    def __init__(self, id, address, city, state, zip_code, deadline, weight, status, dependencies, delay_time=None, truck_id=None):
        self.package_id = id
        self.original_address = address 
        self.address = address 
        self.city = city
        self.state = state
        self.zip_code = zip_code
        self.deadline = deadline
        self.weight = weight
        self.status = status  
        self.dependencies = dependencies 
        self.delay_time = delay_time  
        self.departure_time = None 
        self.delivery_time = None
        self.truck_id = truck_id  

    #Updating the address of package 9, delayed pacakges on flight, and packages dependent on each other and need to be delivered with each other
    def update_status(self, current_time):
        #Correct the address of package 9 either at 10:20am or after
        if self.package_id == 9 and current_time >= timedelta(hours=10, minutes=20):
            self.address = "410 S State St"

        #Return status if package is delayed
        if self.delay_time and current_time < self.delay_time:
            return (
                f"ID: {self.package_id} -- Truck ID: {self.truck_id} -- Address: {self.address} {self.city} {self.state}, {self.zip_code} --"
                f" Weight: {self.weight} -- Deadline: {self.deadline} -- Delayed until {self.delay_time}"
            )

        #Identifying status based on the current time
        if self.delivery_time and current_time >= self.delivery_time:
            status = f"Delivered at {self.delivery_time}"
        elif self.departure_time and current_time >= self.departure_time:
            status = f"En-Route at {current_time}"
        else:
            status = f"At Hub at {current_time}"

        #Identifying and including package dependance info
        dependency_info = ""
        if self.dependencies:
            dependency_info = f" Must be delivered with: {', '.join(map(str, self.dependencies))}"

        return (
            f"ID: {self.package_id} -- Truck ID: {self.truck_id} -- Address: {self.address}, {self.city}, {self.state}, {self.zip_code} --"
            f" Weight: {self.weight} -- Deadline: {self.deadline} -- {status}{dependency_info}"
        )

    #String representation of package
    def __str__(self):
        return (
            f"ID: {self.package_id} -- Truck ID: {self.truck_id} -- Address: {self.address}, {self.city}, {self.state}, {self.zip_code} --"
            f" Weight: {self.weight} -- Deadline: {self.deadline} -- {self.status} at {self.delivery_time}"
        )
