#include <EloquentTinyML.h>
#include "phishing_detection_model_tflite.h"  // Include your model header file

#define NUMBER_OF_INPUTS 30  // Number of input features from your dataset
#define NUMBER_OF_OUTPUTS 1   // Single output since it's binary classification
#define TENSOR_ARENA_SIZE 5*1024  // Adjust size as needed

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

void setup() {
    Serial.begin(115200);
   
    ml.begin(phishing_detection_model_tflite);  // Initialize the model
}

void loop() {
    // Sample input data based on your dataset
    float input1[] = {-1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 
                       1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 
                       -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 
                       -1.0f, -1.0f, -1.0f, 1.0f, 1.0f}; // Input 1
    // Expected Output is 0.0              

    float input2[] = {1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 
                   -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, -1.0f, 
                   -1.0f, 0.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 
                   -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f}; // Input 2
    // Expected Output is 1.0                 

    float fResult[NUMBER_OF_OUTPUTS] = {0};
    float fRes;
    int final_output;  // Declare final_output here

    // Predicting for the first input
    fRes = ml.predict(input1, fResult);
    final_output = (fResult[0] > 0.5f) ? 1 : 0;  // Corrected to use fResult
    Serial.print("\nThe output value returned for input1 is: ");
    Serial.println(final_output); 

    // Predicting for the second input
    fRes = ml.predict(input2, fResult);
    final_output = (fResult[0] > 0.5f) ? 1 : 0;  // Corrected to use fResult
    Serial.print("\nThe output value returned for input2 is: ");
    Serial.println(final_output);      

    delay(5000); // Delay between predictions
}

