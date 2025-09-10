Class: D387 - Advanced Java

Name/WGU ID: Kamren Northrop, 011338614

Task B1:

    •Created Resource bundle "welcome"
        • Created welcome_en.properties(1): initialized welcome message in english.
        • Created welcome_fr.properties(1): initialized welcome message in french.

    •Created translations package for conversions
        • Created DisplayMessage.java(1-14): Retrieves welcome messages using the resource bundle. 
        • Created WelcomeController.java(1-28): Implemented Rest endpoints to return welcome messages in English and French. 

    •Edited D387SampleCodeApplication.java
        •Line 17-34: Initialized a display message instance and created two threads to print welcome messages in English and in French.

    •Edited ApiConfig.java
        •Line 20-23: Configured CORS for /api/** endpoints with the HTTP methods GET and POST.

    •Edited app.component.ts 
        •Line 24-25: Added strings to hold welcome message urls for English and French api calls. 
        •Line 33: Initialized an empty map to hold both english and french message with a string key. 
        •Line 41-42: Fetching English and French welcome messages.
        •Line 94-115: Created functions to retrieve and assign welcome messages in English(key: 'en') and French(key: 'fr') to the map from the backend using a HTTP request. 

    •Edited app.component.html
        •Line 8-9: Displayed the retrieved English and French welcome messages to the webpage.

Task B2:

    •Edited app.component.ts
        •Line 139-140: Added variables CADprice and EURprice to the room interface to hold the CAD and EUR prices.
        •Line 56-76: Edited the onSubmit function to iterate through each room and convert the price from the given USD to CAD and EUR, rounding all three prices to the nearest penny and save to their associated variables.
            •Conversions made with the current exchange rates of: 1 USD = 1.37 CAD, 1 USD = 0.85 EUR.

    •Edited app.component.html
        •Line 81-83: Displayed all 3 currency conversions to the webpage with labels of (USD), (CAD), (EUR) and their associated currency symbols.

Task B3:

    •Created TimeZones class in the translations package 
        •Line 9-19: Created methods that returns a single 12 hour formated string that includes ET, MT, and UTC time zones with the associated AM/PM label.
    
    •Created TimeZoneController in the translation package
        •Line 8-22: Implemented Rest endpoints to return the time zone string. 

    •Edited app.component.ts
        •Line 26: Added string to hold time zone url for api call.
        •Line 34: Initialized empty string to hold formated time zone string returned from get request.
        •Line 44: Added line to call the fetchTimeZones function
        •Line 131-141: Created fetchTimeZones function to retrieve the time zones from the backend using a HTTP request.

    •Edited appcomponent.html
        •Line 41: Displayed time zone string to the web page below "Book for room" with styling for a better presentation. 

Task C1

    •Line 1-14: Created Dockerfile






