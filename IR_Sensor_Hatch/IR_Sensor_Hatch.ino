#include "LinkedList.h"
#include <math.h>

#define ANALOG_NUM_SAMPLES 5
#define NUM_LEDS 27
#define CENTER_INDEX ((NUM_LEDS - 1) / 2)
//#define OFF_THRESHOLD 1100
#define MAX_INTENSITY 8000

double OFF_THRESHOLD = 4200.0;
//double MIN_INTENSITY = -1.0;
//double MAX_INTENSITY = -1.0;

#define MIN(a, b) ((a > b) ? b : a)
#define MAX(a, b) ((a > b) ? a : b)

int indexToAnalogPin[NUM_LEDS] = {A7, A6, A5, A4, A3, A2, A1, A0, A8, A11, A10, A22, A9, A21, A26, A20, A25, A19, A24, A18, A23, A17, A12, A16, A13, A15, A14};

struct runningAverageData
{
  uint16_t samples[ANALOG_NUM_SAMPLES];
  int8_t index = 0;
  uint32_t sum = 0;
  byte count = 0;
};

struct activeLightData
{
  int8_t index;
  uint16_t intensity;
};

struct runningAverageData averages[NUM_LEDS];
LinkedList<struct activeLightData> activeLights;

void setup()
{                
  Serial.begin(38400);
  analogReadResolution(13);
}

long runningAverage(int newValue, int idx)
{
  // keep sum updated to improve speed.
  averages[idx].sum -= averages[idx].samples[averages[idx].index];
  averages[idx].samples[averages[idx].index] = newValue;
  averages[idx].sum += averages[idx].samples[averages[idx].index];

  // update active index of array
  averages[idx].index++;
  averages[idx].index = averages[idx].index % ANALOG_NUM_SAMPLES;

  // update count if we're still populating the array
  if (averages[idx].count < ANALOG_NUM_SAMPLES)
    averages[idx].count++;

  // return the average
  return averages[idx].sum / averages[idx].count;
}

void addActiveLight(int idx, int intensity)
{
  struct activeLightData thisLight;
  thisLight.index = idx;
  thisLight.intensity = MIN(intensity, MAX_INTENSITY);

  int i;
  for(i=0;i<activeLights.size();i++)
  {
    //Insert
    if(intensity > activeLights.get(i).intensity)
    {
      activeLights.add(i, thisLight);
      break;
    }
  }
  //Got to the end without inserting, append to the end
  if(i == activeLights.size())
    activeLights.add(thisLight);
}

void detectLedOn(int idx)
{
  //Read sensor value (analog)
  int val;
  val = analogRead(indexToAnalogPin[idx]);
  //Filter with running average
  val = runningAverage(val, idx);
/*
  if(idx == 0 || idx == 13 || idx == 26)
  {
    Serial.print(val);
    if(idx == 0 || idx == 13)
      Serial.print(",");
    else
      Serial.println();
  }*/

  //Is the sensor triggered?
  bool isOn = val > OFF_THRESHOLD;
  if (isOn)
  {
    //Yes, insert into the activeLights structure
    //Decreasing order, largest to smallest
    addActiveLight(idx, val);
  }
}

void readLights2()
{
  //Read all the lights and build the sum
  uint16_t readings[NUM_LEDS];
  double sum = 0.0;
  for(int i=0; i<NUM_LEDS; i++)
  {
    int val;
    val = analogRead(indexToAnalogPin[i]);
    readings[i] = val;
    sum += (double)val;
  }

  //Calculate the mean, and then the standard deviation
  double mean = sum/NUM_LEDS;
  double stddev = 0.0;
  double diff = 0.0;
  for(int i=0; i<NUM_LEDS; i++)
  {
    diff = readings[i] - mean;
    stddev += (diff * diff);
  }
  stddev /= NUM_LEDS-1;
  stddev = sqrt(stddev);
  OFF_THRESHOLD = (mean + 1.5*stddev);
  Serial.print(mean);
  Serial.print(",");
  Serial.println(stddev);

  //Classify each as on or off
  for(int i=0; i<NUM_LEDS; i++)
  {
    if(readings[i] > OFF_THRESHOLD)
    {
      /*if(MAX_INTENSITY < 0)
        MAX_INTENSITY = readings[i];
      else
        MAX_INTENSITY = MAX(MAX_INTENSITY, readings[i]);
        
      if(MIN_INTENSITY < 0)
        MIN_INTENSITY = readings[i];
      else
        MIN_INTENSITY = MIN(MIN_INTENSITY, readings[i]);*/
        
      addActiveLight(i, readings[i]);
    }
  }
}

void readLights()
{
  for(int i=0; i<NUM_LEDS; i++)
  {
    detectLedOn(i);

    //if(i < (NUM_LEDS-1))
    //  Serial.print(",");
  }
  //Serial.println("");
}

float findBrightestOffset()
{
  //Returns distance of line from left-most light (in inches);

  //If no more lights are active... nothing to find!
  if(activeLights.size() == 0)
  {
    Serial.println("No lights.");
    return 31.875; //-1.0;
  }

  struct activeLightData brightest = activeLights.get(0);
  activeLights.remove(0);

  struct activeLightData adjacentToBrightest;
  adjacentToBrightest.index = -1;
  adjacentToBrightest.intensity = 7777;
  for(int i=0;i<activeLights.size();i++)
  {
    struct activeLightData temp = activeLights.get(i);
    int idx = temp.index;
    if(idx == (brightest.index - 1) || idx == (brightest.index + 1))
    {
      adjacentToBrightest.index = temp.index;
      adjacentToBrightest.intensity = temp.intensity;
      activeLights.remove(i);
      break; 
    }
  }

  if(adjacentToBrightest.index == -1)
  {
    //Brightest stands alone
    //Offset is difference between index and center point
    return ((float)brightest.index);
  }
  else
  {
    //Interpolate between brightest and adjacentToBrightest
    int diff = 0;
    diff = brightest.intensity - adjacentToBrightest.intensity;
    //Diff needs to be right-most minus left-most, so if brightest is to the left of adjacent, flip the sign
    if(brightest.index < adjacentToBrightest.index)
      diff *= -1;

    float diff_off = ((float)diff)/((MAX_INTENSITY - OFF_THRESHOLD));
    //float diff_off = ((float)diff)/((MAX_INTENSITY - MIN_INTENSITY));
    float off = 0.5 + diff_off;

    return MIN(brightest.index, adjacentToBrightest.index) + off;
  }
}

float findOffset()
{
  float val1, val2, retval;
  val1 = findBrightestOffset();
  val2 = findBrightestOffset();
  retval = 0.0;
  
  if(val2 > 30)
  {
    //We don't see a second line
    retval = val1;
  }
  else
  {
    //We have two brightest offsets... return the one closest to the center
    float diff1 = fabs(val1 - CENTER_INDEX);
    float diff2 = fabs(val2 - CENTER_INDEX);
    if(diff1 < diff2)
      retval = val1;
    else
      retval = val2;
  }
  
  Serial.println(retval);
  return retval;
}

void loop()                     
{
  activeLights.clear();

  //Read all the sensor values and build our list of active lights
  readLights();
  //Serial.print(activeLights.size());

  //Analyze our list of active lights and calculate our offset
  float val1 = findBrightestOffset();
  float val2 = findBrightestOffset();
  analogWrite(2, (int)(val1 * 8));
  analogWrite(3, (int)(val2 * 8));
  
  delay(25);
}
