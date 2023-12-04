#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{
    int arrivalTime;
    int eventTime;
    EventClass eventElement;
    if(travelDir == EAST_DIRECTION){
        arrivalTime = getPositiveNormal(eastArrivalMean, eastArrivalStdDev);
        eventTime = currentTime + arrivalTime;
        eventElement = EventClass(eventTime, EVENT_ARRIVE_EAST);
        eventList.insertValue(eventElement);
        cout << "Time: " << currentTime << " Scheduled " << eventElement << endl;
    }
    else if(travelDir == WEST_DIRECTION){
        arrivalTime = getPositiveNormal(westArrivalMean, westArrivalStdDev);
        eventTime = currentTime + arrivalTime;
        eventElement = EventClass(eventTime, EVENT_ARRIVE_WEST);
        eventList.insertValue(eventElement);
        cout << "Time: " << currentTime << " Scheduled " << eventElement << endl;
    }
    else if(travelDir == NORTH_DIRECTION){
        arrivalTime = getPositiveNormal(northArrivalMean, northArrivalStdDev);
        eventTime = currentTime + arrivalTime;
        eventElement = EventClass(eventTime, EVENT_ARRIVE_NORTH);
        eventList.insertValue(eventElement);
        cout << "Time: " << currentTime << " Scheduled " << eventElement << endl;
    }
    else if(travelDir == SOUTH_DIRECTION){
        arrivalTime = getPositiveNormal(southArrivalMean, southArrivalStdDev);
        eventTime = currentTime + arrivalTime;
        eventElement = EventClass(eventTime, EVENT_ARRIVE_SOUTH);
        eventList.insertValue(eventElement);
        cout << "Time: " << currentTime << " Scheduled " << eventElement << endl;
    }
}

void IntersectionSimulationClass::scheduleLightChange(
     )
{
    int eventTime = 0;
    EventClass eventElement;
    if(currentLight == LIGHT_GREEN_EW){
        eventTime = currentTime + eastWestGreenTime;
        eventElement = EventClass(eventTime, EVENT_CHANGE_YELLOW_EW);
        eventList.insertValue(eventElement);
        cout << "Time: " << currentTime << " Scheduled " << eventElement << endl;
    }
    else if(currentLight == LIGHT_YELLOW_EW){
        eventTime = currentTime + eastWestYellowTime;
        eventElement = EventClass(eventTime, EVENT_CHANGE_GREEN_NS);
        eventList.insertValue(eventElement);
        cout << "Time: " << currentTime << " Scheduled " << eventElement << endl;
    }
    else if(currentLight == LIGHT_GREEN_NS){
        eventTime = currentTime + northSouthGreenTime;
        eventElement = EventClass(eventTime, EVENT_CHANGE_YELLOW_NS);
        eventList.insertValue(eventElement);
        cout << "Time: " << currentTime << " Scheduled " << eventElement << endl;
    }
    else if(currentLight == LIGHT_YELLOW_NS){
        eventTime = currentTime + northSouthYellowTime;
        eventElement = EventClass(eventTime, EVENT_CHANGE_GREEN_EW);
        eventList.insertValue(eventElement);
        cout << "Time: " << currentTime << " Scheduled " << eventElement << endl;
    }
}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
    EventClass handledEvent;
    eventList.removeFront(handledEvent);
    currentTime = handledEvent.getTimeOccurs();

    if((currentTime <= timeToStopSim)){
        cout << endl;
        cout << "Handling " << handledEvent << endl;

        //Handling Car Arrivals, enque carClass to their respective FIFOQueueclass
        if(handledEvent.getType() == EVENT_ARRIVE_EAST){

            CarClass carEast = CarClass(EAST_DIRECTION, currentTime);
            eastQueue.enqueue(carEast);

            cout << "Time: " << currentTime << " Car #" << carEast.getId() <<
                 " arrives east-bound - queue length: " << eastQueue.getNumElems() << endl;

            //schedule next arrival
            scheduleArrival(EAST_DIRECTION);

            if (eastQueue.getNumElems() > maxEastQueueLength){
                //count the longest east queue
                maxEastQueueLength = eastQueue.getNumElems();
            }
        }
        else if(handledEvent.getType() == EVENT_ARRIVE_WEST){

            CarClass carWest = CarClass(WEST_DIRECTION, currentTime);
            westQueue.enqueue(carWest);

            cout << "Time: " << currentTime << " Car #" <<  carWest.getId() <<
                 " arrives west-bound - queue length: " << westQueue.getNumElems() << endl;

            scheduleArrival(WEST_DIRECTION);

            if(westQueue.getNumElems() > maxWestQueueLength){
                maxWestQueueLength = westQueue.getNumElems();
            }
        }
        else if(handledEvent.getType() == EVENT_ARRIVE_NORTH){

            CarClass carNorth = CarClass(NORTH_DIRECTION, currentTime);
            northQueue.enqueue(carNorth);

            cout << "Time: " << currentTime << " Car #" << carNorth.getId() <<
                 " arrives north-bound - queue length: " << northQueue.getNumElems() <<
                 endl;

            scheduleArrival(NORTH_DIRECTION);

            if(northQueue.getNumElems() > maxNorthQueueLength){
                maxNorthQueueLength = northQueue.getNumElems();
            }
        }
        else if(handledEvent.getType() == EVENT_ARRIVE_SOUTH){

            CarClass carSouth = CarClass(SOUTH_DIRECTION, currentTime);
            southQueue.enqueue(carSouth);

            cout << "Time: " << currentTime << " Car #" << carSouth.getId() <<
                 " arrives south-bound - queue length: " << southQueue.getNumElems() <<
                 endl;

            scheduleArrival(SOUTH_DIRECTION);

            if(southQueue.getNumElems() > maxSouthQueueLength){
                //count the longest east queue
                maxSouthQueueLength = southQueue.getNumElems();
            }
        }

            //Traffic lights
            //Handling east-west traffic through green light
        else if(handledEvent.getType() == EVENT_CHANGE_YELLOW_EW){
            int numAdvancedEast = 0;
            int numAdvancedWest = 0;

            cout << "Advancing cars on east-west green" << endl;

            while((eastQueue.getNumElems() != 0) && (numAdvancedEast <
                                                     eastWestGreenTime)){
                CarClass dequeCar;
                eastQueue.dequeue(dequeCar);

                cout << "  Car #" << dequeCar.getId() << " advances east-bound" << endl;
                numAdvancedEast += 1;
            }

            while((westQueue.getNumElems() != 0) && (numAdvancedWest <
                                                     eastWestGreenTime)) {
                CarClass dequeCar;
                westQueue.dequeue(dequeCar);

                cout << "  Car #" << dequeCar.getId() << " advances west-bound" << endl;
                numAdvancedWest += 1;
            }

            cout << "East-bound cars advanced on green: " << numAdvancedEast <<
                 " Remaining queue: " << eastQueue.getNumElems() << endl;


            cout << "West-bound cars advanced on green: " << numAdvancedWest <<
                 " Remaining queue: " << westQueue.getNumElems() << endl;

            numTotalAdvancedEast += numAdvancedEast;
            numTotalAdvancedWest += numAdvancedWest;

            //Light Change to EW Yellow
            currentLight = LIGHT_YELLOW_EW;
            scheduleLightChange();
        }

            //Handling north-south traffic through green light
        else if(handledEvent.getType() == EVENT_CHANGE_YELLOW_NS){
            int numAdvancedNorth = 0;
            int numAdvancedSouth = 0;

            cout << "Advancing cars on north-south green" << endl;


            while((northQueue.getNumElems() != 0) && (numAdvancedNorth <
                                                      northSouthGreenTime)){
                CarClass dequeCar;
                northQueue.dequeue(dequeCar);

                cout << "  Car #" << dequeCar.getId() << " advances north-bound" <<
                     endl;
                numAdvancedNorth += 1;
            }

            while((southQueue.getNumElems() != 0) && (numAdvancedSouth <
                                                      northSouthGreenTime)){
                CarClass dequeCar;
                southQueue.dequeue(dequeCar);

                cout << "  Car #" << dequeCar.getId() << " advances south-bound" <<
                     endl;
                numAdvancedSouth += 1;
            }

            cout << "North-bound cars advanced on green: " << numAdvancedNorth <<
                 " Remaining queue: " << northQueue.getNumElems() << endl;


            cout << "South-bound cars advanced on green: " << numAdvancedSouth <<
                 " Remaining queue: " << southQueue.getNumElems() << endl;

            numTotalAdvancedNorth += numAdvancedNorth;
            numTotalAdvancedSouth += numAdvancedSouth;

            //Light Change to NS Yellow
            currentLight = LIGHT_YELLOW_NS;
            scheduleLightChange();
        }

            //Handling east-west traffic through yellow light
        else if(handledEvent.getType() == EVENT_CHANGE_GREEN_NS){
            int numAdvancedEast = 0;
            int numAdvancedWest = 0;
            bool ifStopAtYellowEast = NOT_STOP;
            bool ifStopAtYellowWest = NOT_STOP;
            //variables that shows whether the car stops on yellow or not

            cout << "Advancing cars on east-west yellow" << endl;

            while((eastQueue.getNumElems() != 0) && (numAdvancedEast <
                                                     eastWestYellowTime) && (ifStopAtYellowEast == NOT_STOP)){
                int passValue = getUniform(1, 100);
                if(passValue > percentCarsAdvanceOnYellow){
                    cout << "  Next east-bound car will NOT advance on yellow" << endl;
                    ifStopAtYellowEast = STOP_WHEN_YELLOW;
                }
                    //Will advance on yelllow
                else{
                    CarClass dequeCar;
                    eastQueue.dequeue(dequeCar);
                    cout << "  Next east-bound car will advance on yellow" << endl;
                    cout << "  Car #" << dequeCar.getId() << " advances east-bound"
                         << endl;
                    numAdvancedEast += 1;
                }

            }
            if(eastQueue.getNumElems() == 0){
                cout << "  No east-bound cars waiting to advance on yellow" << endl;
            }

            while((westQueue.getNumElems() != 0) && (numAdvancedWest <
                                                     eastWestYellowTime) && (ifStopAtYellowWest == NOT_STOP)){
                int passValue = getUniform(1, 100);
                if(passValue > percentCarsAdvanceOnYellow){
                    cout << "  Next west-bound car will NOT advance on yellow" << endl;
                    ifStopAtYellowWest = STOP_WHEN_YELLOW;
                }
                    //Will advance on yelllow
                else{
                    CarClass dequeCar;
                    westQueue.dequeue(dequeCar);
                    cout << "  Next west-bound car will advance on yellow" << endl;
                    cout << "  Car #" << dequeCar.getId() << " advances west-bound" <<
                         endl;
                    numAdvancedWest += 1;
                }
            }
            if(westQueue.getNumElems() == 0){
                cout << "  No west-bound cars waiting to advance on yellow" << endl;
            }

            cout << "East-bound cars advanced on yellow: " << numAdvancedEast <<
                 " Remaining queue: " << eastQueue.getNumElems() << endl;


            cout << "West-bound cars advanced on yellow: " << numAdvancedWest <<
                 " Remaining queue: " << westQueue.getNumElems() << endl;

            numTotalAdvancedEast += numAdvancedEast;
            numTotalAdvancedWest += numAdvancedWest;

            //Light Change to NS Green
            currentLight = LIGHT_GREEN_NS;
            scheduleLightChange();
        }

            //Handling north-south traffic through yellow light
        else if(handledEvent.getType() == EVENT_CHANGE_GREEN_EW){
            int numAdvancedNorth = 0;
            int numAdvancedSouth = 0;
            bool ifStopAtYellowNorth = NOT_STOP;
            bool ifStopAtYellowSouth = NOT_STOP;

            cout << "Advancing cars on north-south yellow" << endl;

            while((northQueue.getNumElems() != 0) && (numAdvancedNorth <
                                                      northSouthYellowTime) && (ifStopAtYellowNorth == NOT_STOP)){
                int passValue = getUniform(1, 100);
                if(passValue > percentCarsAdvanceOnYellow){
                    cout << "  Next north-bound car will NOT advance on yellow" << endl;
                    ifStopAtYellowNorth = STOP_WHEN_YELLOW;
                }
                    //Will advance on yelllow
                else{
                    CarClass dequeCar;
                    northQueue.dequeue(dequeCar);
                    cout << "  Next north-bound car will advance on yellow" << endl;
                    cout << "  Car #" << dequeCar.getId() << " advances north-bound"
                         << endl;
                    numAdvancedNorth += 1;
                }

            }
            if(northQueue.getNumElems() == 0){
                cout << "  No north-bound cars waiting to advance on yellow" << endl;
            }


            while((southQueue.getNumElems() != 0) && (numAdvancedSouth <
                                                      northSouthYellowTime) && (ifStopAtYellowSouth == NOT_STOP)){
                int passValue = getUniform(1, 100);
                if(passValue > percentCarsAdvanceOnYellow){
                    cout << "  Next south-bound car will NOT advance on yellow" << endl;
                    ifStopAtYellowSouth = STOP_WHEN_YELLOW;
                }
                    //Will advance on yelllow
                else{
                    CarClass dequeCar;
                    southQueue.dequeue(dequeCar);
                    cout << "  Next south-bound car will advance on yellow" << endl;
                    cout << "  Car #" << dequeCar.getId() << " advances south-bound"
                         << endl;
                    numAdvancedSouth += 1;
                }
            }
            if(southQueue.getNumElems() == 0){
                cout << "  No south-bound cars waiting to advance on yellow" << endl;
            }

            cout << "North-bound cars advanced on yellow: " << numAdvancedNorth <<
                 " Remaining queue: " << northQueue.getNumElems() << endl;


            cout << "South-bound cars advanced on yellow: " << numAdvancedSouth <<
                 " Remaining queue: " << southQueue.getNumElems() << endl;

            numTotalAdvancedNorth += numAdvancedNorth;
            numTotalAdvancedSouth += numAdvancedSouth;

            //Light Change to EW Green
            currentLight = LIGHT_GREEN_EW;
            scheduleLightChange();

        }
        return true;
    }

    cout << endl;
    cout << "Next event occurs AFTER the simulation end time ";

    cout << "(" << handledEvent << ")!" << endl;

    return false;
}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
