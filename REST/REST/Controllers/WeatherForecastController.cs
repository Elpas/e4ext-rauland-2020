using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json.Linq;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Dynamic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;


namespace REST.Controllers
{
    [ApiController]
    [Route("[controller]")]
    [Produces("application/json")]
    public class WeatherForecastController : ControllerBase
    {
        private static readonly string[] Summaries = new[]
        {
            "Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
        };

        private readonly ILogger<WeatherForecastController> _logger;

        public WeatherForecastController(ILogger<WeatherForecastController> logger)
        {
            _logger = logger;
        }

        [HttpGet]
        public IEnumerable<WeatherForecast> Get()
        {
            var rng = new Random();
            return Enumerable.Range(1, 5).Select(index => new WeatherForecast
            {
                Date = DateTime.Now.AddDays(index),
                TemperatureC = rng.Next(-20, 55),
                Summary = Summaries[rng.Next(Summaries.Length)]
            })
            .ToArray();
        }

        public class Version1
        {
            public string brand;
            public string VendorSourceName;
            public string version;
            public string timestamp;
        }

      
        [HttpGet("/version")]
        public ContentResult Version()
        {
           

            String utc = DateTime.UtcNow.ToString("yyyy-MM-ddTHH\\:mm\\:ssZ"); //.fffffffzzz");

           /* var obj = new Version1
            {
             
                brand= "Rtls Make" ,
                VendorSourceName= "RTLS east wing" ,
                version= "Alpha - 5.2",
                timestamp= "2018-06-28T17:48:18Z"

            }*/
             var obj = new Version1
             {

                 brand = "Rtls Make",
                 VendorSourceName = "RTLSVENDOR1",
                 version = "Alpha-5.2",
                 timestamp = utc

             };
              var jsonString = Newtonsoft.Json.JsonConvert.SerializeObject(obj);
         
            /*string final = "Version Result";
            final += jsonString;
           
            */


            Console.WriteLine(jsonString);
            // return jsonString;
            return Content(jsonString, "application/json");

        }

        public class tagsResponse
        {

            public Int32 total;
            public ArrayList  tags;
        }



        [HttpGet("/tags")]
        public ContentResult Tags()
        {
               
            string skip = HttpContext.Request.Query["skip"].ToString();
            string top = HttpContext.Request.Query["top"].ToString();

            ArrayList arr = MyFunctions.readFile("rauland_badges.txt");
            tagsResponse res = new tagsResponse();
            res.total = arr.Count;
            res.tags = new ArrayList();

            int nSkip = Convert.ToInt32(skip);
            int nTop= Convert.ToInt32(top);
            for (int  i= nSkip;( i<(nSkip + nTop) && i<arr.Count); i++)
            {
                JObject o =(JObject) arr[i];
                string name = (string)o["Name"];
                res.tags.Add(name);

            }

            var jsonString = Newtonsoft.Json.JsonConvert.SerializeObject(res);


            Console.WriteLine(jsonString);
            MyFunctions.writeFile("return Tag Request(skip=" + skip.ToString() + " top=" + top.ToString() + "=> " + jsonString);

            return Content(jsonString, "application/json");
           // return jsonString.ToString();

        }
        public class locationsResponse
        {

            public Int32 total;
            public ArrayList locations;
        }

        [HttpGet("/locations")]
        public ContentResult Locations()
        {

            string skip = HttpContext.Request.Query["skip"].ToString();
            string top = HttpContext.Request.Query["top"].ToString();

            ArrayList arr = MyFunctions.readFile("rauland_readers.txt");
            locationsResponse res = new locationsResponse();
            res.total = arr.Count;
            res.locations = new ArrayList();

            int nSkip = Convert.ToInt32(skip);
            int nTop = Convert.ToInt32(top);
            for (int i = nSkip; (i < (nSkip + nTop) && i < arr.Count); i++)
            {
                JObject o = (JObject)arr[i];
                string name = (string)o["Name"];
                res.locations.Add(name);

            }

            var jsonString = Newtonsoft.Json.JsonConvert.SerializeObject(res);


            Console.WriteLine(jsonString);
            MyFunctions.writeFile("return Locatiom Request(skip="+skip.ToString()+" top="+top.ToString()+"=> " + jsonString); 
            return Content(jsonString, "application/json");
         //   return jsonString.ToString();

        }




    }
}
