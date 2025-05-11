import os
import requests
from bs4 import BeautifulSoup
import json

# Get the absolute path of the script
script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, "data.json")
URL = "https://aro.lfv.se/Links/Link/ViewLink?TorLinkId=314&type=MET"
data = {}

#Make request
req = requests.get(URL)
print("Status: " + str(req.status_code))

#Parse the contents
text = BeautifulSoup(req.text, 'html.parser')
divs = text.find_all("div", {"class": "tor-link-text-row no-background"})

#Save Last updated value
lastUpdateDiv = divs[0]
lastUpdateDiv.find("span", {"class": "item-text"})
data["lastUpdated"] = lastUpdateDiv.text.strip() 


divs = divs[1::]

#Save the METAR data
stationData = []
for div in divs: 
    #Parse the ICAO code and the weather data
    icaoCode = div.find("span", {"class": "item-header"}).text.strip() 
    weatherData = div.find("span", {"class": "item-text"}).text.strip()
    
    #Save it to the array
    stationData.append({"ICAO": icaoCode, "weatherData": weatherData})

#Add the station array to the json data object
data["stations"] = stationData



#Write to file
with open(file_path, "w") as file:
    json.dump(data, file)