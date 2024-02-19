#include <iostream>
#include <fstream>
#include <vector>
#include <TFile.h>
#include <TH1F.h>
#include <TMath.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int Sum_BackWWJET_energy_json_log() {
    // Cargar el archivo JSON
    std::ifstream jsonFile("BackWWJET_energy.json");
    json jsonData;
    jsonFile >> jsonData;

    // Variables para almacenar las secciones transversales y las luminosidades
    Double_t crossSection = 10.7165;  // en pb
    Double_t luminosity = 1.5e6;  // 1.5 ab^-1 expresado en pb^-1

    // Histograma acumulativo para almacenar la suma de los histogramas normalizados
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
        TH1F* hist = dynamic_cast<TH1F*>(file.Get("JET"));

        // Normaliza el histograma
        if (hist) {
            // Obtiene el número de eventos del histograma actual
            int events = hist->GetEntries();

            // Suma los eventos al total de eventos generados
            generatedEvents += events;

            // Normaliza el histograma por la sección transversal, luminosidad y la relación de eventos finales sobre eventos generados
            Double_t scaleFactor = crossSection * luminosity * static_cast<Double_t>(events) / generatedEvents;
            hist->Scale(scaleFactor);

            // Si es el primer archivo, crea el histograma acumulativo
            if (!cumulativeHist) {
                cumulativeHist = new TH1F(*hist);
                cumulativeHist->SetDirectory(nullptr);  // Desvincula el histograma del archivo
            } else {
                cumulativeHist->Add(hist);  // Agrega el histograma normalizado al histograma acumulativo
            }

            // Suma los eventos al total de eventos finales
            finalEvents += events;
        } else {
            std::cerr << "Error: No se pudo obtener el histograma del archivo " << outputFile << std::endl;
        }
    }

    // Verifica si se obtuvieron eventos generados y finales
    if (generatedEvents == 0 || finalEvents == 0) {
        std::cerr << "Error: No se pudieron obtener los eventos generados y finales" << std::endl;
        return 1;
    }

    // Calcula la relación de eventos finales sobre eventos generados
    Double_t finalToGeneratedRatio = static_cast<Double_t>(finalEvents) / generatedEvents;

    // Imprime la relación de eventos finales sobre eventos generados
    std::cout << "Relación de eventos finales sobre eventos generados: " << finalToGeneratedRatio << std::endl;

    // Guarda el histograma acumulativo normalizado en un nuevo histograma con escala logarítmica
    TH1F* logHist = new TH1F(*cumulativeHist);
    for (int i = 1; i <= logHist->GetNbinsX(); ++i) {
        double binContent = logHist->GetBinContent(i);
        if (binContent > 0) {
            logHist->SetBinContent(i, TMath::Log10(binContent));
        }
    }

    // Guarda el histograma con escala logarítmica en un archivo ROOT
    const char* outputFileName = "Sum_BackWWJET_energy_histogram_json_log1.root";
    TFile outputFileObj(outputFileName, "RECREATE");
    logHist->Write();
    outputFileObj.Close();

    std::cout << "Histograma con escala logarítmica guardado en " << outputFileName << std::endl;

    delete cumulativeHist;  // Libera la memoria del histograma acumulativo
    delete logHist;  // Libera la memoria del histograma con escala logarítmica

    return 0;
}
