#!/usr/bin/env python
import phonenumbers as pn
import opencage as oc
import folium as fl

if (x:=input("sel: ")) == "y":
    from myphone import number
else:
    number = x

from mykey import key

from phonenumbers import geocoder as gc
from phonenumbers import carrier as cr

from opencage.geocoder import OpenCageGeocode

pepnumber = pn.parse(number)
location = gc.description_for_number(pepnumber, "en")
carrier = cr.name_for_number(pepnumber, "en")

geocoder = OpenCageGeocode(key)
query = str(location)
rslt = geocoder.geocode(query)

lat = rslt[0]['geometry']['lat']
lng = rslt[0]['geometry']['lng']

myMap = fl.Map(location=[lat, lng], zoom_start=9)
fl.Marker([lat,lng], popup=location).add_to(myMap)

myMap.save("mylocations.html")

print(f"Country: {location}\nCarrier: {carrier}\nLocation: {lat}, {lng}")