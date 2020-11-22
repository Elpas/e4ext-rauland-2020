using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
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
        public string Version()
        {

            String utc = DateTime.UtcNow.ToString("yyyy-MM-ddTHH\\:mm\\:ssZ"); //.fffffffzzz");

            var obj = new Version1
            {
             
                brand= "Rtls Make" ,
                VendorSourceName= "RTLS east wing" ,
                version= "Alpha - 5.2",
                timestamp= "2018-06-28T17:48:18Z"

            };
         
            var jsonString = Newtonsoft.Json.JsonConvert.SerializeObject(obj);

           
            Console.WriteLine(jsonString);
            return jsonString.ToString();

        }
        [HttpGet("/tags")]
        public string Tags()
        {
               
            string skip = HttpContext.Request.Query["skip"].ToString();
            string top = HttpContext.Request.Query["top"].ToString();






            String utc = DateTime.UtcNow.ToString("yyyy-MM-ddTHH\\:mm\\:ssZ"); //.fffffffzzz");

            var obj = new Version1
            {

                brand = "Rtls Make",
                VendorSourceName = "RTLS east wing",
                version = "Alpha - 5.2",
                timestamp = "2018-06-28T17:48:18Z"

            };

            var jsonString = Newtonsoft.Json.JsonConvert.SerializeObject(obj);


            Console.WriteLine(jsonString);
            return jsonString.ToString();

        }
    }
}
