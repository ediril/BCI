using System;
using System.Collections.Generic;
using System.Text;
using System.Media;
using System.Threading;
using Dragonfly;


namespace sound_maker
{
    class Program
    {
        static void Main(string[] args)
        {
            bool KeepRunning = true;
            Module mod = new Module();
            SoundPlayer player = new SoundPlayer();

            string config_dir = System.Environment.GetEnvironmentVariable("BCI_CONFIG");
            string[] SoundLocations = new string[] {
                                    String.Format("{0}\\default\\reward.wav", config_dir),
                                    String.Format("{0}\\default\\failure.wav", config_dir),
                                    String.Format("{0}\\default\\success.wav", config_dir),
                                };

            string mm_ip = "localhost:7111";
            if (args.Length > 0)
                mm_ip = args[0];

            //player.SoundLocation = String.Format("{0}\\default\\reward.wav", config_fld);
            //player.Load();

            // Create a module and connect to Message Manager
            mod.ConnectToMMM(0, mm_ip);

            // Subscribe to messages
            mod.Subscribe(MT.GIVE_REWARD);
            mod.Subscribe(MT.PLAY_SOUND);
            //mod.Subscribe(MT.EXIT);

            // Let Application Manager know we are ready
            mod.SendModuleReady();

            Console.WriteLine("Connected to {0}", mm_ip);


            Message m;
            while (KeepRunning)
            {
                try
                {
                    m = mod.ReadMessage(Module.ReadType.Blocking);

                    if (m.msg_type == MT.GIVE_REWARD)
                    {
                        player.SoundLocation = SoundLocations[0];
                        player.Load();
                        player.PlaySync();

                        MDF.GIVE_REWARD rd = new MDF.GIVE_REWARD();
                        object o = rd;
                        m.GetData(ref o);
                        Console.WriteLine("GIVE_REWARD {0} {1}", rd.duration_ms, rd.num_clicks);
                    }
                    else if (m.msg_type == MT.PLAY_SOUND)
                    {
                        MDF.PLAY_SOUND ps = new MDF.PLAY_SOUND();
                        object o = ps;
                        m.GetData(ref o);

                        if (ps.id < SoundLocations.Length)
                        {
                            player.SoundLocation = SoundLocations[ps.id];
                            player.Load();
                            player.PlaySync();
                            Console.WriteLine("PLAY_SOUND id: {0}", ps.id);
                        }
                        else
                            Console.WriteLine("ERROR: Invalid sound id: {0}", ps.id);
                    }
                    //else if (m.msg_type == MT.EXIT)
                    //{
                    //    KeepRunning = false;
                    //}
                }
                catch
                {
                    Console.WriteLine("ERROR: Something went wrong...");
                    KeepRunning = false;
                }
            }

            mod.DisconnectFromMMM();
        }
    }
}
