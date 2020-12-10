using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Collections;
using Newtonsoft.Json.Linq;
using System.Net;
using System.IO;
using System.Net.Http;

namespace core3.Controllers
{
    public class MyFunctions
    {
       

    public static string SendHttpGet(string url)
        {

            var handler = new HttpClientHandler();

            handler.ServerCertificateCustomValidationCallback +=
                            (sender, certificate, chain, errors) =>
                            {
                                return true;
                            };

            HttpClient client = new HttpClient(handler);
            var result = client.GetAsync(url).Result;



            HttpClientHandler clientHandler = new HttpClientHandler();
            clientHandler.ServerCertificateCustomValidationCallback = (sender, cert, chain, sslPolicyErrors) => { 
                return true; 
            };
            ServicePointManager.ServerCertificateValidationCallback += (sender, certificate, chain, errors) =>
            {
                // local dev, just approve all certs
               return true;
              
            };


            // Pass the handler to httpclient(from you are calling api)
           // HttpClient client = new HttpClient(clientHandler);
         //   var result = client.GetAsync(url).Result;


            HttpClient httpClient = new HttpClient();
            //var result = httpClient.GetAsync(url).Result;


            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            request.AutomaticDecompression = DecompressionMethods.GZip | DecompressionMethods.Deflate;

            using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
            using (Stream stream = response.GetResponseStream())
            using (StreamReader reader = new StreamReader(stream))
            {
                return reader.ReadToEnd();
            }
            return "";
        }
        public static ArrayList readFile(string fileName)
        {
            string path = @"C:\Eiris\e41srv\Data\Rauland\";
            ArrayList arr = new ArrayList();
            int counter = 0;
            string line;

            // Read the file and display it line by line.  
            System.IO.StreamReader file =
                new System.IO.StreamReader(path + fileName);
            while ((line = file.ReadLine()) != null)
            {
                JObject json = JObject.Parse(line);
                arr.Add(json);

               // System.Console.WriteLine(line);
                counter++;
            }

            file.Close();
            //System.Console.WriteLine("There were {0} lines.", counter);
            // Suspend the screen.  
            //System.Console.ReadLine();

            return arr;

        }
    }
}
