package main

import (
  "SVO.AERO/src/simulatedAnnealing"
  "SVO.AERO/src/tableData/abstractTables"
  "SVO.AERO/src/tableData/tables"
  "fmt"
  "time"
)

func main() {
  folder := "/Users/arseniytrofimov/Desktop/SVO/SVO.AERO/data/"

  start := time.Now()

  planes := tables.Planes{}
  planes.LoadData(folder + "Timetable_private.csv")
  pplaces := tables.ParkingPlaces{}
  pplaces.LoadData(folder + "Aircraft_Stands_Private.csv")
  timeHandling := tables.HTime{}
  timeHandling.LoadData(folder + "Handling_Time_Private.csv")
  ratesHandling := tables.Rates{}
  ratesHandling.LoadData(folder + "Handling_Rates_Private.csv")
  data := abstractTables.AirportData{&ratesHandling, &timeHandling, &pplaces, &planes}

  simulatedAnnealing.Anneal(&data, 10000, 100., 0.999999, 1, folder + "Timetable_private.csv", folder + "output.csv")
  elapsed := time.Since(start)
  fmt.Println("It took ", elapsed)
}
