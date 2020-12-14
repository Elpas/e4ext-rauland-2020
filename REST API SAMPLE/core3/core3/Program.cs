using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace core3
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
                    opt.ListenAnyIP(5000);
                    Console.WriteLine("AAAAAAAAAAAAAA"); 
                });

                webBuilder.UseStartup<Startup>();
            });
    }
}
