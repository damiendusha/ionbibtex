
===== What is this project? =====

The Institute of Navigation* (ION) is a technical society specialising in 
navigation-related topics. They produce an academic journal and several 
conferences for both academia and industry.

Unfortunantly, they offer no "export citation" functionalty for those that 
manage their papers using BibTeX (or other citation manager). This project is
a simple screen scraper to extract the nessessary citation information and 
format it as a BibTeX citation.

* N.B. This project is not endorsed by, and is no way affiliated with ION.
I am an ordinary member of ION with a subscription to the digital library.
Hopefully, ION will offer an "export citation" functionalty directly, making
this project completely redundant.


===== What platforms are targeted? =====

Initially, POSIX platforms (especially Ubuntu) which is my primary operating 
system. It should also work "out of the box" for Apple Mac, but I don't have 
a system to test with.

Windows support will come one day, but will be mostly untested since I rarely
use it.  Patches, of course, will be welcome.


===== What licence does it use? =====

The program is licenced under GPLv2 or (at your option) any later version.
Please see "LICENCE.txt" for the full terms and conditions.

There are long-term plans to create a library from the core files and perhaps
create a GUI for users that want one.  At this point, the core libraries will
probably be re-licenced as LGPL, but that decision will be made later.


===== What dependences does it have? =====

  * Boost
  * Curl
  * Standard POSIX system (Note: These interfaces will be progressively
    removed in favour of Boost or standard library functions)
  * CMake (for building)


===== TODO =====

  * Out-of-source builds
  * "Post-processing" (e.g. a JabRef exporter)
  * Cross-platform building


===== Questions? =====

Sure! Please email me at d.dusha@gmail.com - I'd like to know what you think
of it.

  -- Damien Dusha, 23rd June 2013.


