#include <iostream>
#include <TFile.h>
#include <TH1F.h>

int Test_SignalJET_mass() {
    const char* fileNames[] = {
        "SignalJET_mass_events_019839222.root",
        "SignalJET_mass_events_027985022.root",
        "SignalJET_mass_events_067618566.root",
        "SignalJET_mass_events_075207014.root",
        "SignalJET_mass_events_088898158.root",
        "SignalJET_mass_events_090014287.root",
        "SignalJET_mass_events_129556080.root",
        "SignalJET_mass_events_138935081.root",
        "SignalJET_mass_events_176415634.root",
        "SignalJET_mass_events_177743949.root",
        "SignalJET_mass_events_178769856.root",
        "SignalJET_mass_events_192707663.root",
        "SignalJET_mass_events_008995949.root",
        "SignalJET_mass_events_061640142.root",
        "SignalJET_mass_events_107858353.root",
        "SignalJET_mass_events_174244458.root",
        "SignalJET_mass_events_180776309.root",
        "SignalJET_mass_events_065244791.root",
        "SignalJET_mass_events_034459462.root",
        "SignalJET_mass_events_071153275.root",
        "SignalJET_mass_events_090844778.root",
        "SignalJET_mass_events_158628525.root" 
    };

    // Variables para almacenar las secciones transversales y las luminosidades.
    Double_t crossSection = 0.05394;  // en pb
    Double_t luminosity = 2.4e6;  // 2.4 ab^-1 expresado en pb^-1

    // Crea un histograma acumulativo para almacenar la suma de los histogramas.
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

        // Agrega el histograma al histograma acumulativo.
        if (hist) {
            if (!cumulativeHist) {
                cumulativeHist = new TH1F(*hist);
                cumulativeHist->SetDirectory(nullptr);  // Desvincula el histograma del archivo.
            } else {
                cumulativeHist->Add(hist);  // Agrega el histograma al histograma acumulativo.
            }
        } else {
            std::cerr << "Error: No se pudo obtener el histograma del archivo " << fileNames[i] << std::endl;
        }
    }

    if (cumulativeHist) {
        // Normaliza el histograma acumulativo.
        cumulativeHist->Scale(crossSection * luminosity);  // Normalización por sección transversal y luminosidad.

        // Guarda el histograma acumulativo normalizado en un nuevo archivo.
        const char* outputFileName = "Test_SignalJET_mass_histogram.root";
        TFile outputFileObj(outputFileName, "RECREATE");
        cumulativeHist->Write();
        outputFileObj.Close();

        std::cout << "Histograma normalizado guardado en " << outputFileName << std::endl;

        delete cumulativeHist;  // Libera la memoria del histograma acumulativo.
    }

    return 0;
}

int main() {
    Test_SignalJET_mass();  // Llamada a la función principal.

    return 0;
}
