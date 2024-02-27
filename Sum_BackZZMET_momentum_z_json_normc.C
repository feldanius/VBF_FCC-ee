#include <iostream>
#include <fstream>
#include <vector>
#include <TFile.h>
#include <TH1F.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int Sum_BackZZMET_momentum_z_json_normc() {
    // Cargar el archivo JSON
    std::ifstream jsonFile("BackZZMET_momentum_z.json");
    json jsonData;
    jsonFile >> jsonData;

    // Variables para almacenar las secciones transversales y las luminosidades
    Double_t crossSection = 0.6428;  // en pb
    Double_t luminosity = 1.5e6;  // 1.5 ab^-1 expresado en pb^-1

    // Histograma acumulativo para almacenar la suma de los histogramas
    TH1F* cumulativeHist = nullptr;

    // Variables para almacenar el número de eventos generados y finales
    int generatedEvents = 0;
    int finalEvents = 0;

    // Recorrer los elementos del archivo JSON
    for (const auto& entry : jsonData) {
        std::string inputFile = entry["InputFile"];
        std::string outputFile = entry["OutputFile"];

        // Abre el archivo ROOT de salida
        TFile file(outputFile.c_str());

        // Comprueba si se abrió correctamente el archivo
        if (file.IsZombie()) {
            std::cerr << "Error: No se pudo abrir el archivo " << outputFile << std::endl;
            continue;
        }

        // Intenta obtener el histograma directamente del archivo
        TH1F* hist = dynamic_cast<TH1F*>(file.Get("MET"));

        // Normaliza el histograma
        if (hist) {
            // Obtiene el número de eventos del histograma actual
            int events = hist->GetEntries();

            // Suma los eventos al total de eventos generados
            generatedEvents += events;

            // Si es el primer archivo, crea el histograma acumulativo
            if (!cumulativeHist) {
                cumulativeHist = new TH1F(*hist);
                cumulativeHist->SetDirectory(nullptr);  // Desvincula el histograma del archivo
            } else {
                cumulativeHist->Add(hist);  // Agrega el histograma al histograma acumulativo
            }

            // Suma los eventos al total de eventos finales
            finalEvents += events;
        } else {
            std::cerr << "Error: No se pudo obtener el histograma del archivo " << outputFile << std::endl;
        }
    }
    // Restaurar la salida estándar
    gSystem->RedirectOutput(0);

    // Verifica si se obtuvieron eventos generados y finales
    if (generatedEvents == 0 || finalEvents == 0) {
        std::cerr << "Error: No se pudieron obtener los eventos generados y finales" << std::endl;
        return 1;
    }

    // Imprime el número de eventos antes de la normalización
    std::cout << "Número de eventos antes de la normalización: " << finalEvents << std::endl;

    // Normaliza el histograma acumulativo por la sección transversal, luminosidad y la relación de eventos finales sobre eventos generados
    Double_t scaleFactor = crossSection * luminosity * static_cast<Double_t>(finalEvents) / generatedEvents;
    cumulativeHist->Scale(scaleFactor);

    // Imprime el número de eventos después de la normalización
    int finalEventsNormalized = cumulativeHist->GetEntries();
    std::cout << "Número de eventos después de la normalización: " << finalEventsNormalized << std::endl;

    // Calcula la relación de eventos finales sobre eventos generados
    Double_t finalToGeneratedRatio = static_cast<Double_t>(finalEvents) / generatedEvents;

    // Imprime la relación de eventos finales sobre eventos generados
    std::cout << "Relación de eventos finales sobre eventos generados: " << finalToGeneratedRatio << std::endl;

    // Guarda el histograma acumulativo normalizado en un nuevo archivo
    const char* outputFileName = "Sum_BackZZMET_momentum_z_histogram_json_normc.root";
    TFile outputFileObj(outputFileName, "RECREATE");
    cumulativeHist->Write();
    outputFileObj.Close();

    std::cout << "Histograma normalizado guardado en " << outputFileName << std::endl;

    delete cumulativeHist;  // Libera la memoria del histograma acumulativo

    return 0;
}
