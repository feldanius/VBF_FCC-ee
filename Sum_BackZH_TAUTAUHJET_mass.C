#include <iostream>
#include <TFile.h>
#include <TH1F.h>

int Sum_BackZH_TAUTAUHJET_mass() {
    const char* fileNames[] = {
"JET_BackZH_TAUTAUH_mass_events_015660911.root",
"JET_BackZH_TAUTAUH_mass_events_058437289.root",
"JET_BackZH_TAUTAUH_mass_events_094523955.root",
"JET_BackZH_TAUTAUH_mass_events_160031364.root",
"JET_BackZH_TAUTAUH_mass_events_175873169.root",
"JET_BackZH_TAUTAUH_mass_events_192276123.root",
"JET_BackZH_TAUTAUH_mass_events_043999218.root",
"JET_BackZH_TAUTAUH_mass_events_090181769.root",
"JET_BackZH_TAUTAUH_mass_events_116046380.root",
"JET_BackZH_TAUTAUH_mass_events_162671919.root",
"JET_BackZH_TAUTAUH_mass_events_186940475.root"
    };

    // Variables para almacenar las secciones transversales y las luminosidades.
    Double_t crossSection = 0.004172;  // en pb
    Double_t luminosity = 2.4e6;  // 2.4 ab^-1 expresado en pb^-1

    // Crea un histograma acumulativo para almacenar la suma de los histogramas normalizados.
    TH1F* cumulativeHist = nullptr;

    for (int i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); ++i) {
        // Abre el archivo ROOT.
        TFile file(fileNames[i]);

        // Comprueba si se abrió correctamente el archivo.
        if (file.IsZombie()) {
            std::cerr << "Error: No se pudo abrir el archivo " << fileNames[i] << std::endl;
            continue;
        }

        // Intenta obtener el histograma directamente del archivo.
        TH1F* hist = dynamic_cast<TH1F*>(file.Get("JET"));

        // Normaliza el histograma.
        if (hist) {
            hist->Scale(crossSection * luminosity );  // Normalización por sección transversal y luminosidad.

            // Si es el primer archivo, crea el histograma acumulativo.
            if (!cumulativeHist) {
                cumulativeHist = new TH1F(*hist);
                cumulativeHist->SetDirectory(nullptr);  // Desvincula el histograma del archivo.
            } else {
                cumulativeHist->Add(hist);  // Agrega el histograma normalizado al histograma acumulativo.
            }
        } else {
            std::cerr << "Error: No se pudo obtener el histograma del archivo " << fileNames[i] << std::endl;
        }
    }

    if (cumulativeHist) {
        // Guarda el histograma acumulativo normalizado en un nuevo archivo.
        const char* outputFileName = "BackZH_TAUTAUHJET_mass_histogram.root";
        TFile outputFileObj(outputFileName, "RECREATE");
        cumulativeHist->Write();
        outputFileObj.Close();

        std::cout << "Histograma normalizado guardado en " << outputFileName << std::endl;

        delete cumulativeHist;  // Libera la memoria del histograma acumulativo.
    }

    return 0;
}

int main() {
    Sum_BackZH_TAUTAUHJET_mass();  // Llamada a la función principal.

    return 0;
}
