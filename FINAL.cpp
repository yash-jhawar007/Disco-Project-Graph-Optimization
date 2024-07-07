#include <bits/stdc++.h>
using namespace std;
vector<pair<string,pair<string,string>>> out = {};

// Function to assign courses for Elective (EL) category
void assigncoursesEL(vector<string> x1, vector<string> x2, vector<string> x3, vector<string> profs, vector<string> courses, vector<pair<string, int>> graph[])
{
    // Calculate average preference for each professor
    vector<double> avpref = {};
    for (int i = 0; i < profs.size(); i++)
    {
        double sum = 0;
        int count = 0;
        for (int j = 0; j < graph[i].size(); j++)
        {
            if (graph[i][j].second != 0)
            {
                sum += graph[i][j].second;
                count++;
            }
        }
        avpref.push_back(sum / count);
    }

    // Find the course with the minimum average preference
    int min = INT_MAX;
    int minindex = 0;
    for (int j = 0; j < courses.size(); j++)
    {
        if (min > avpref[j] && avpref[j] != 0)
        {
            min = avpref[j];
            minindex = j;
        }
    }

    // Find the professor with the maximum preference for the selected course
    int maximum = INT_MIN;
    vector<int> interestedprofs = {};
    for (int k = 0; k < profs.size(); k++)
    {
        if (graph[k][minindex].second > maximum)
        {
            maximum = graph[k][minindex].second;
        }
    }

    // Store professors with the maximum preference for the selected course
    for (int k = 0; k < profs.size(); k++)
    {
        if (graph[k][minindex].second == maximum)
        {
            interestedprofs.push_back(k);
        }
    }

    // Create pairs of professors who are interested in the same course
    vector<pair<int, int>> profpair;
    for (auto it = interestedprofs.begin(); it != interestedprofs.end(); it++)
    {
        if (*it < x1.size())
        {
            for (auto it1 = it + 1; it1 != interestedprofs.end(); it1++)
            {
                profpair.push_back(make_pair(*it, *it1));
            }
        }
        else if (*it >= x1.size())
        {
            for (auto it1 = it; it1 != interestedprofs.end(); it1++)
            {
                profpair.push_back(make_pair(*it, *it1));
            }
        }
    }

    // Iterate over pairs of professors interested in the same course
    for (auto it : profpair)
    {
        vector<string> newprofs = {};
        vector<string> newx1 = x1;
        vector<string> newx2 = x2;
        vector<string> newx3 = x3;
        vector<string> newcourses = courses;


        out.push_back(make_pair(courses[minindex],make_pair(profs[it.first],profs[it.second])));

        // Adjust professor and course lists based on availability
        if (it.first < x1.size())
        {
            // Professor is in x1 category
            auto iterat = remove(newx1.begin(), newx1.end(), profs[it.first]);
            newx1.erase(iterat, newx1.end());
            if (it.second < x1.size())
            {
                auto iterat1 = remove(newx1.begin(), newx1.end(), profs[it.second]);
                newx1.erase(iterat1, newx1.end());
            }
            else if (it.second < x1.size() + x2.size())
            {
                auto iterat1 = remove(newx2.begin(), newx2.end(), profs[it.second]);
                newx2.erase(iterat1, newx2.end());
                newx1.push_back(profs[it.second]);
            }
            else
            {
                auto iterat1 = remove(newx3.begin(), newx3.end(), profs[it.second]);
                newx3.erase(iterat1, newx3.end());
                newx2.push_back(profs[it.second]);
            }
        }
        else if (it.first >= x1.size())
        {
            // Professor is in x2 or x3 category
            if (it.first == it.second)
            {
                if (it.first < x1.size() + x2.size())
                {
                    auto iterate = remove(newx2.begin(), newx2.end(), profs[it.first]);
                    newx2.erase(iterate, newx2.end());
                }
                else
                {
                    auto iterate = remove(newx3.begin(), newx3.end(), profs[it.first]);
                    newx3.erase(iterate, newx3.end());
                    newx1.push_back(profs[it.first]);
                }
            }
            else
            {
                if (it.first < x1.size() + x2.size())
                {
                    auto iterat1 = remove(newx2.begin(), newx2.end(), profs[it.first]);
                    newx2.erase(iterat1, newx2.end());
                    newx1.push_back(profs[it.first]);
                }
                else
                {
                    auto iterat1 = remove(newx3.begin(), newx3.end(), profs[it.first]);
                    newx3.erase(iterat1, newx3.end());
                    newx2.push_back(profs[it.first]);
                }
                if (it.second < x2.size() + x1.size())
                {
                    auto iterat1 = remove(newx2.begin(), newx2.end(), profs[it.second]);
                    newx2.erase(iterat1, newx2.end());
                    newx1.push_back(profs[it.second]);
                }
                else
                {
                    auto iterat1 = remove(newx3.begin(), newx3.end(), profs[it.second]);
                    newx3.erase(iterat1, newx3.end());
                    newx2.push_back(profs[it.second]);
                }
            }
        }

        // Update the course list
        newcourses = courses;
        newcourses.erase(newcourses.begin() + minindex);

        // Combine professor lists
        newprofs.insert(newprofs.end(), newx1.begin(), newx1.end());
        newprofs.insert(newprofs.end(), newx2.begin(), newx2.end());
        newprofs.insert(newprofs.end(), newx3.begin(), newx3.end());

        fstream myfile;
        myfile.open("output.txt", ios::out);
        // Recursively call the function with updated parameters
        if (newcourses.size() != 0)
        {
            if(newprofs.size() == 0){
                
            for(int i = 0; i < out.size(); i++){
                myfile << out[i].first << ": " << out[i].second.first << " " << out[i].second.second << endl;
            }
        
            }
            
            assigncoursesEL(newx1, newx2, newx3, newprofs, newcourses, graph);
           
        }
        else{
            for(int i = 0; i < out.size(); i++){
                myfile << out[i].first << ": " << out[i].second.first << " " << out[i].second.second << endl;
            }
            myfile << " " << endl;
            myfile << " " << endl;
        }
    }
}
// Function to assign courses for CDC category
vector<vector<string>> assigncoursesCDC(vector<string> x1, vector<string> x2, vector<string> x3, vector<string> profs, vector<string> courses, vector<string> coursesEL, vector<pair<string, int>> graph[], vector<pair<string, int>> graphEL[], int n)
{
    try
    {

        // Calculate average preference for each professor
        vector<double> avpref = {};
        vector<string> updatedprofs = {};
        vector<string> updatedx1 = {};
        vector<string> updatedx2 = {};
        vector<string> updatedx3 = {};

        for (int i = 0; i < n; i++)
        {
            int count = 0;
            double sum = 0;
            for (int j = 0; j < graph[i].size(); j++)
            {
                if (graph[i][j].second != 0)
                {
                    sum += graph[i][j].second;
                    count++;
                }
            }
            if (count == 0)
            {
                // Handle the scenario where all weightages are zero
                throw runtime_error("All weightages of CDC courses are zero.");
            }
            avpref.push_back(sum / count);
        }

        // Find the course with the maximum average preference
        int max = INT_MIN;
        int maxindex = 0;
        for (int j = 0; j < courses.size(); j++)
        {
            if (max < avpref[j] && avpref[j] != 0)
            {
                max = avpref[j];
                maxindex = j;
            }
        }

        // Find the professor with the minimum preference for the selected course
        int minimum = INT_MAX;
        vector<int> interestedprofs = {};
        for (int k = 0; k < profs.size(); k++)
        {
            if (graph[k][maxindex].second < minimum)
            {
                minimum = graph[k][maxindex].second;
            }
        }

        // Store professors with the minimum preference for the selected course
        for (int k = 0; k < profs.size(); k++)
        {
            if (graph[k][maxindex].second == minimum)
            {
                interestedprofs.push_back(k);
            }
        }

        // Create pairs of professors who are interested in the same course
        vector<pair<int, int>> profpair;
        for (auto it = interestedprofs.begin(); it != interestedprofs.end(); it++)
        {
            if (*it < x1.size())
            {
                for (auto it1 = it + 1; it1 != interestedprofs.end(); it1++)
                {
                    profpair.push_back(make_pair(*it, *it1));
                }
            }
            else if (*it >= x1.size())
            {
                for (auto it1 = it; it1 != interestedprofs.end(); it1++)
                {
                    profpair.push_back(make_pair(*it, *it1));
                }
            }
        }
       
        // Iterate over pairs of professors interested in the same course
        for (auto it : profpair)
        {
            vector<string> newprofs = {};
            vector<string> newx1 = x1;
            vector<string> newx2 = x2;
            vector<string> newx3 = x3;
            vector<string> newcourses = courses;

         
            out.push_back(make_pair(courses[maxindex],make_pair(profs[it.first],profs[it.second])));

            // Adjust professor and course lists based on availability
            if (it.first < x1.size())
            {
                auto iterat = remove(newx1.begin(), newx1.end(), profs[it.first]);
                newx1.erase(iterat, newx1.end());
                if (it.second < x1.size())
                {
                    auto iterat1 = remove(newx1.begin(), newx1.end(), profs[it.second]);
                    newx1.erase(iterat1, newx1.end());
                }
                else if (it.second < x1.size() + x2.size())
                {
                    auto iterat1 = remove(newx2.begin(), newx2.end(), profs[it.second]);
                    newx2.erase(iterat1, newx2.end());
                    newx1.push_back(profs[it.second]);
                }
                else
                {
                    auto iterat1 = remove(newx3.begin(), newx3.end(), profs[it.second]);
                    newx3.erase(iterat1, newx3.end());
                    newx2.push_back(profs[it.second]);
                }
            }
            else if (it.first >= x1.size())
            {
                if (it.first == it.second)
                {
                    if (it.first < x1.size() + x2.size())
                    {
                        auto iterate = remove(newx2.begin(), newx2.end(), profs[it.first]);
                        newx2.erase(iterate, newx2.end());
                    }
                    else
                    {
                        auto iterate = remove(newx3.begin(), newx3.end(), profs[it.first]);
                        newx3.erase(iterate, newx3.end());
                        newx1.push_back(profs[it.first]);
                    }
                }
                else
                {
                    if (it.first < x1.size() + x2.size())
                    {
                        auto iterat1 = remove(newx2.begin(), newx2.end(), profs[it.first]);
                        newx2.erase(iterat1, newx2.end());
                        newx1.push_back(profs[it.first]);
                    }
                    else
                    {
                        auto iterat1 = remove(newx3.begin(), newx3.end(), profs[it.first]);
                        newx3.erase(iterat1, newx3.end());
                        newx2.push_back(profs[it.first]);
                    }
                    if (it.second < x2.size() + x1.size())
                    {
                        auto iterat1 = remove(newx2.begin(), newx2.end(), profs[it.second]);
                        newx2.erase(iterat1, newx2.end());
                        newx1.push_back(profs[it.second]);
                    }
                    else
                    {
                        auto iterat1 = remove(newx3.begin(), newx3.end(), profs[it.second]);
                        newx3.erase(iterat1, newx3.end());
                        newx2.push_back(profs[it.second]);
                    }
                }
            }

            // Update the course list
            newcourses.erase(newcourses.begin() + maxindex);

            // Combine professor lists
            newprofs.insert(newprofs.end(), newx1.begin(), newx1.end());
            newprofs.insert(newprofs.end(), newx2.begin(), newx2.end());
            newprofs.insert(newprofs.end(), newx3.begin(), newx3.end());

            // Recursively call the function with updated parameters
            if (newcourses.size() != 0)
            {   

                assigncoursesCDC(newx1, newx2, newx3, newprofs, newcourses, coursesEL, graph, graphEL, n);
              
                updatedprofs = newprofs;
                updatedx1 = newx1;
                updatedx2 = newx2;
                updatedx3 = newx3;
            }
            else
            {
                assigncoursesEL(newx1, newx2, newx3, newprofs, coursesEL, graphEL);
             
            }
        }

        // Create a collection of updated lists and return
        vector<vector<string>> collection = {updatedx1, updatedx2, updatedx3, updatedprofs};
        return collection;
    }
    catch (const exception &e)
    {

        // Handle exceptions and print an error message
        cerr << "Exception: " << e.what() << endl;
        return {};
    }
}

int main()
{
    // Declare vectors for professor categories and courses
    vector<string> x1, x2, x3, profs = {};

    // Read professor categories from the file "newname.txt"
    ifstream inputFile;
    inputFile.open("profListERROR.txt", ios::in);

    string line, word;
    int line_no = 0;
    int line_x1 = 2;
    int line_x2 = 5;
    int line_x3 = 8;

    // Read professor categories and store them in vectors x1, x2, and x3
    while (getline(inputFile, line))
    {
        line_no++;
        if (line_no == line_x1)
        {
            // Parse the line and populate vector x1
            istringstream s(line);
            while (s >> word)
            {
                x1.push_back(word);
            }
        }
        else if (line_no == line_x2)
        {
            // Parse the line and populate vector x2
            istringstream s(line);
            while (s >> word)
            {
                x2.push_back(word);
            }
        }
        else if (line_no == line_x3)
        {
            // Parse the line and populate vector x3
            istringstream s(line);
            while (s >> word)
            {
                x3.push_back(word);
            }
        }
    }
    inputFile.close();

    // Combine professor categories into the profs vector
    profs.insert(profs.end(), x1.begin(), x1.end());
    profs.insert(profs.end(), x2.begin(), x2.end());
    profs.insert(profs.end(), x3.begin(), x3.end());

    // Declare vectors for CDC and EL courses
    vector<string> coursesCDC = {};
    vector<string> coursesEL = {};

    // Read CDC and EL courses from the file "newname.txt"
    ifstream inputFile1;
    inputFile1.open("profListERROR.txt", ios::in);

    string line1, word1;
    int line_num = 0;
    int line_CDC = 11;
    int line_cdc = 13;
    int line_ELE = 15;
    int line_ele = 17;

    // Read CDC and EL courses and store them in vectors coursesCDC and coursesEL
    while (getline(inputFile1, line1))
    {
        line_num++;
        if (line_num == line_CDC || line_num == line_cdc)
        {
            // Parse the line and populate vector coursesCDC
            istringstream s(line1);
            while (s >> word1)
            {
                coursesCDC.push_back(word1);
            }
        }
        else if (line_num == line_ELE || line_num == line_ele)
        {
            // Parse the line and populate vector coursesEL
            istringstream s(line1);
            while (s >> word1)
            {
                coursesEL.push_back(word1);
            }
        }
    }
    inputFile1.close();

    // Get the number of professors and CDC courses
    int n = profs.size();
    int m = coursesCDC.size();

    // Create a graph for CDC courses with the given preferences
    vector<pair<string, int>> graphCDC[n + m];

    // Read CDC preferences from the file "testcaseCDC.txt"
    ifstream inputFile2;
    inputFile2.open("testcaseCDC_ERROR.txt", ios::in);

    if (!inputFile2.is_open())
    {
        cerr << "Error opening the file." << endl;
        return 1;
    }

    string line2, word2;
    int line_n = 0;

    // Read CDC preferences and construct the graph
    while (getline(inputFile2, line2))
    {
        if (!line2.empty())
        {
            if (line2.find("Prof") != string::npos)
            {
                // Professor name line
                line_n++;
                continue;
            }
            else
            {
                // Course preference line
                istringstream s(line2);
                s >> word2;
                int x = stoi(word2);
                s >> word2;

                graphCDC[line_n - 1].push_back(make_pair(word2, x));
            }
        }
    }
    inputFile2.close();

    // Get the number of professors and EL courses
    int nEL = profs.size();
    int mEL = coursesEL.size();

    // Create a graph for EL courses with the given preferences
    vector<pair<string, int>> graphEL[nEL + mEL];

    // Read EL preferences from the file "testcaseEL.txt"
    ifstream inputFile3;
    inputFile3.open("testcaseEL_ERROR.txt", ios::in);

    if (!inputFile3.is_open())
    {
        cerr << "Error opening the file." << endl;
        return 1;
    }

    string line3, word3;
    int line_n1 = 0;

    // Read EL preferences and construct the graph
    while (getline(inputFile3, line3))
    {
        if (!line3.empty())
        {
            if (line3.find("Prof") != string::npos)
            {
                // Professor name line
                line_n1++;
                continue;
            }
            else
            {
                // Course preference line
                istringstream s(line3);
                s >> word3;
                int x1 = stoi(word3);
                s >> word3;

                graphEL[line_n1 - 1].push_back(make_pair(word3, x1));
            }
        }
    }
    inputFile3.close();

    // Call the function to assign CDC courses
    assigncoursesCDC(x1, x2, x3, profs, coursesCDC, coursesEL, graphCDC, graphEL, n);



    return 0;
}
