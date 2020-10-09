#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>

int main(int argc, char** argv)
{
    std::string sport = "", subSport = "", event = "";
    std::ifstream input;
    std::ofstream output;
    bool hasSubSport = false;
    if (argc == 2)
    {
        std::string name = argv[1];
        name += ".txt";
        input.open(name.c_str(), std::ios::in);
        if (input.fail())
        {
            return 0;
        }
    }
    else
    {
        input.open("entries.txt", std::ios::in);
        if (input.fail())
        {
            return 0;
        }
    }
    while(!input.eof())
    {
        std::string nextLine = "";
        std::getline(input, nextLine);
        if (nextLine == "")
        {
            // Blank line means reset
            sport = "";
            subSport = "";
            event = "";
        }
        else if (nextLine.find(';') == std::string::npos)
        {
            // Not an entry
            if (sport == "")
            {
                // Next line contains a sport name
                sport = nextLine;
                std::transform(sport.begin(), sport.end(), sport.begin(), ::toupper); // Change the sport name to uppercase
                if (sport == "BOBSLEIGH" || sport == "SKATING" || sport == "SKIING" || sport == "AQUATICS" || sport == "CANOEING" || sport == "CYCLING"
                        || sport == "EQUESTRIAN" || sport == "GYMNASTICS" || sport == "VOLLEYBALL" || sport == "WRESTLING")
                {
                    hasSubSport = true;
                }
                else
                {
                    hasSubSport = false;
                }
            }
            else if (hasSubSport && subSport == "")
            {
                // Next line contains a subsport name
                subSport = nextLine;
                std::transform(subSport.begin(), subSport.end(), subSport.begin(), ::toupper); // Change the subsport name to uppercase
            }
            else
            {
                bool isSubSport = false;
                if (hasSubSport)
                {
                    // Check if the nextline is a subSport
                    std::string upperNext = nextLine;
                    std::transform(upperNext.begin(), upperNext.end(), upperNext.begin(), ::toupper);
                    if (sport == "BOBSLEIGH")
                    {
                        if (upperNext == "BOBSLEIGH" || upperNext == "SKELETON")
                        {
                            isSubSport = true;
                        }
                    }
                    else if (sport == "SKATING")
                    {
                        if (upperNext == "FIGURE SKATING" || upperNext == "SHORT TRACK SPEED SKATING" || upperNext == "SPEED SKATING")
                        {
                            isSubSport = true;
                        }
                    }
                    else if (sport == "SKIING")
                    {
                        if (upperNext == "ALPINE SKIING" || upperNext == "CROSS-COUNTRY SKIING" || upperNext == "FREESTYLE SKIING" || upperNext == "NORDIC COMBINED"
                                || upperNext == "SKI JUMPING" || upperNext == "SNOWBOARDING")
                        {
                            isSubSport = true;
                        }
                    }
                    else if (sport == "AQUATICS")
                    {
                        if (upperNext == "DIVING" || upperNext == "SWIMMING" || upperNext == "SYNCHRONIZED SWIMMING" || upperNext == "WATER POLO")
                        {
                            isSubSport = true;
                        }
                    }
                    else if (sport == "CANOEING")
                    {
                        if (upperNext == "SLALOM" || upperNext == "SPRINT")
                        {
                            isSubSport = true;
                        }
                    }
                    else if (sport == "CYCLING")
                    {
                        if (upperNext == "BMX" || upperNext == "MOUNTAIN BIKING" || upperNext == "ROAD" || upperNext == "TRACK")
                        {
                            isSubSport = true;
                        }
                    }
                    else if (sport == "EQUESTRIAN")
                    {
                        if (upperNext == "DRESSAGE" || upperNext == "EVENTING" || upperNext == "JUMPING")
                        {
                          isSubSport = true;  
                        }
                    }
                    else if (sport == "GYMNASTICS")
                    {
                        if (upperNext == "ARTISTIC" || upperNext == "RHYTHMIC" || upperNext == "TRAMPOLINE")
                        {
                            isSubSport = true;
                        }
                    }
                    else if (sport == "VOLLEYBALL")
                    {
                        if (upperNext == "BEACH" || upperNext == "INDOOR")
                        {
                            isSubSport = true;
                        }
                    }
                    else if (sport == "WRESTLING")
                    {
                        if (upperNext == "FREESTYLE" || upperNext == "GRECO-ROMAN")
                        {
                            isSubSport = true;
                        }
                    }
                }
                if (!isSubSport)
                {
                    // Next line contains an event name
                    event = nextLine;
                }
                else
                {
                    // Next line contains a subsport name
                subSport = nextLine;
                event = "";
                }
            }
        }
        else
        {
            // Next line contains entry
            // Determine appropriate file and print it
            // First, make sure that the entry is entered in a sport and an event
            if (sport == "" || event == "")
            {
                // Signup is invalid, so tell me where the error is and throw an assertion
                std::cout << "Sport: " << sport << std::endl;
                if (hasSubSport)
                {
                    std::cout << "Sub-Sport: " << subSport << std::endl;
                }
                std::cout << "Event: " << event << std::endl;
                std::cout << "Next Line: " << nextLine << std::endl;
                assert (false);
            }
            else if (hasSubSport && subSport == "")
            {
                // Signup is invalid, so tell me where the error is and throw an assertion
                std::cout << "Sport: " << sport << std::endl;
                std::cout << "Sub-Sport: " << subSport << std::endl;
                std::cout << "Event: " << event << std::endl;
                std::cout << "Next Line: " << nextLine << std::endl;
                assert (false);
            }
            
            // Next, determine the file name
            std::string outputFileName = "", tempEvent = event;
            char genderFlag = '0';
            if (sport.find("(") != std::string::npos)
            {
                sport = sport.substr(0, (sport.find("(") - 1));
            }
            outputFileName += sport;
            if (hasSubSport)
            {
                outputFileName += "-";
                outputFileName += subSport;
            }
            outputFileName += " ";
            if (tempEvent.find("Women") != std::string::npos)
            {
                // If the event is a women's event, remove "Women's" from the event name and set the gender flag
                genderFlag = 'W';
                if (tempEvent.length() > 8)
                {
                    tempEvent = tempEvent.substr(8, (tempEvent.length() - 8));
                }
                else
                {
                    tempEvent = "";
                }
            }
            else if (tempEvent.find("Men") != std::string::npos)
            {
                // If the event is a men's event, remove "Men's" from the event name and set the gender flag
                genderFlag = 'M';
                
                if (tempEvent.length() > 6)
                {
                    tempEvent = tempEvent.substr(6, ((tempEvent.length() - 6)));
                }
                else
                {
                    tempEvent = "";
                }
            }
            if (genderFlag == 'M' || genderFlag == 'W')
            {
                outputFileName += genderFlag;
            }
            if (tempEvent.find("(") != std::string::npos)
            {
                if (tempEvent.at(0) != '(')
                {
                    tempEvent = tempEvent.substr(0, (tempEvent.find("(") - 1));
                }
                else
                {
                    tempEvent = "";
                }
            }
            if (tempEvent != "")
            {
                outputFileName += " ";
                outputFileName += tempEvent;
            }
            outputFileName += ".txt";
            
            // Open the appropriate file, append the output to it and close the file.
            std::ofstream output;
            output.open(outputFileName.c_str(), std::ios::app);
            output << nextLine << std::endl;
            output.close();
        }
    }
    input.close();
    return 0;
}
