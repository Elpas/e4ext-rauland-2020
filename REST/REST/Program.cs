using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using REST.Controllers;
namespace REST
{
    public class Program
    {
        public static void Main(string[] args)
        {
            CreateHostBuilder(args).Build().Run();
        }

        public static IHostBuilder CreateHostBuilder(string[] args) =>
          Host.CreateDefaultBuilder(args)
            .ConfigureServices((context, services) =>
            {

            })
            .ConfigureWebHostDefaults(webBuilder =>
            {
                webBuilder.ConfigureKestrel(opt =>
                {
                    /* opt.ListenAnyIP(5001, listenOpt =>
                     {
                         listenOpt.UseHttps(
                          @"D:\localshop.pfx",
                           "pa55w0rd!");
                     });*/
                    MyFunctions.writeFile("going to ConfigureKestrel on port 10770");
                    opt.ListenAnyIP(10770);
                    Console.WriteLine("configured Kestrel ok\r\n");
                    MyFunctions.writeFile("Done  Kestrel config");

                });

                webBuilder.UseStartup<Startup>();
            });
    }
}
