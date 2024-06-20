#include <iostream>
#include <TFile.h>
#include <TH1F.h>

int Sum_BackZH_MUMUHJET_mass() {
    const char* fileNames[] = {
"JET_BackZH_MUMUH_mass_events_023261681.root",
"JET_BackZH_MUMUH_mass_events_034927544.root",
"JET_BackZH_MUMUH_mass_events_058572739.root",
"JET_BackZH_MUMUH_mass_events_073291643.root",
"JET_BackZH_MUMUH_mass_events_092281869.root",
"JET_BackZH_MUMUH_mass_events_189404834.root",
"JET_BackZH_MUMUH_mass_events_033570460.root",
"JET_BackZH_MUMUH_mass_events_036028207.root",
"JET_BackZH_MUMUH_mass_events_068513877.root",
"JET_BackZH_MUMUH_mass_events_075232335.root",
"JET_BackZH_MUMUH_mass_events_183713990.root",
"JET_BackZH_MUMUH_mass_events_197337122.root"
    };

    // Variables para almacenar las secciones transversales y las luminosidades.
    Double_t crossSection = 0.004185;  // en pb
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
        const char* outputFileName = "BackZH_MUMUHJET_mass_histogram.root";
        TFile outputFileObj(outputFileName, "RECREATE");
        cumulativeHist->Write();
        outputFileObj.Close();

        std::cout << "Histograma normalizado guardado en " << outputFileName << std::endl;

        delete cumulativeHist;  // Libera la memoria del histograma acumulativo.
    }

    return 0;
}

int main() {
    Sum_BackZH_MUMUHJET_mass();  // Llamada a la función principal.

    return 0;
}
