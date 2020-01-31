#include "../include/weightsParser.h"

std::vector<std::string> readJoints(ifstream& flux){ //skip jusque OFFSET
    string ligne;
    std::vector<std::string> jointNames;
    getline(flux >> std::ws, ligne);
    std::string delimiter = " ";
    size_t pos = 0;
    int counter = 0;
    std::string token;
    while ((pos = ligne.find(delimiter)) != std::string::npos) {
        token = ligne.substr(0, pos);
        // std::cout << counter << " " <<token << std::endl;
        if(counter>0) jointNames.push_back(token);
        ligne.erase(0, pos + delimiter.length());
        counter ++;
    }
    jointNames.push_back(ligne);
    return jointNames;

}
std::vector<double> readWeights(ifstream& flux, int &id){ //skip jusque OFFSET
    string ligne;
    std::vector<double> weights;
    getline(flux >> std::ws, ligne);
    stringstream ss(ligne);
    ss >> id;
    size_t pos = 0;
    int counter = 0;
    double token;
    while (ss >> token) {
        weights.push_back(token);
    }
    return weights;

}

std::vector<std::vector<double>> getWeights(){
    string argFile = "viewer/models/weights.txt";
    std::vector<std::vector<double>> verteciesWeightMap;
    // if(argFile.empty()){
    //     cout << "No file was given to parse"<<endl;
    //     exit(1);
    // }
    string ligne;
    ifstream flux(argFile);
    if(flux)
    {
        cout << "Début de parsing des poids " << endl;
        std::vector<std::string> jointNames = readJoints(flux);
        int id = 0;
        while(flux){
            //std::cout << id << std::endl;
            verteciesWeightMap.push_back(readWeights(flux, id));
        }
        if(verteciesWeightMap.back().size() == 0){
            verteciesWeightMap.pop_back();
        }
    }else{
        std::cerr <<"Pas de flux 2"<<"\n";
    }
    return verteciesWeightMap;
}


// int main(int argc, char *argv[]){
//     // std::cout << "coucou" << argv[1] << "\n";
//     // if(argv[1]){
//     //     parse(argv[1]);
//     // }
//     parse();

//     return 0;
// }
