import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.i2ctool.I2cif 1.0
import melexis.driver 1.0

Page {
    id: probePage
    property string deviceName: "/dev/i2c-1"

    allowedOrientations: Orientation.All
    SilicaFlickable
    {
    Grid
                {
                    Button
                    {
                        id: probeBTN
                        text: "check camera present"
                        onClicked: {probeBTN.text="probing..."; i2cif.tohVddSet("on"); i2cif.i2cProbe(deviceName)}
                    }
                    Label
                    {

                        id: resultLabel
                        text: "0"
                    }

                }
    }

    I2cif
    {
        id: i2cif

        onI2cProbingChanged:
        {
            var results = i2cif.i2cProbingStatus;
            for (var i=0 ; i<i2cif.i2cProbingStatus.length ; i++)
            {
                var res = results[i]
                if(res === "ok"){
                    resultLabel.text = i;
                    break;
                }
            }

            probeBTN.text = "probe done";
            thermal.fuzzyInit();
        }
    }

    MLX90640{
        id: thermal

        onDataReady:
        {
            var image = thermal.imageVect;
            resultLabel.text = image[200];
        }
    }
}
