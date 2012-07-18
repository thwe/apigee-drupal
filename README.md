#APIGEE STANDARD DRUPAL DISTRIBUTION

##Requirements
 
* Apache 2.2 or newer (njinx prolly works but is unsupported)
* PHP 5.3.6 or newer (php 5.2 is EOL'd, 5.4 is preferred)
* A Unix/Linux-based server. Windows is an unsupported server install
* MySQL 5.1 or newer
* Drush 5.0 or newer (see install instructions)
 

##A note about workflow
We recommend working with Apigee-Drupal/APIPortal locally and then moving your changes upstream to a staging environment then moving those changes from staging to a production environment. For that reason, we recommend using a local version of the *AMP stack. 

###Mac OS Install
Your mac has a default version of PHP installed. Feel free to install drupal in /Library/Webserver/Documents if you are only working on a single site. If you need to work on multiple web projects that need their own hostanme, we recommend [MAMP Pro](http://www.mamp.info). MAMP Pro installs multiple versions of PHP in a container and allows you to do virtual hosting with a great deal of ease. For a few words about making MAMP Pro the default PHP on your mac, see this [blog entry](http://stovak.net/blog/install-drush-5-mamp-pro). 

###Windows Install
For Windows, WAMP is a good choice. Installing [Cygwin](http://www.cygwin.com) is recommended for completely shell scripting compatibility.

###Linux Install
For linux, use your distribution's latest PHP stack.  

##Continuous Integration
Keeping Drupal up-to-date can be a full-time job. This is why every time code is pushed out to Apigee's development environment, a Drush Make process is run and the site is built with the latest version of every module unless there's a reason to link to a specific version of that module. All of [Apigee's](http://www.apigee.com) hosting is done with CENTOS 6.x/Amazon's distro of linux. We use use [Puppet](http://puppetlabs.com) to manage our server infrastructure and server software updates. We use Jenkins to do software builds, including Apigee Drupal. We use [Phing](http://phing.info) to manage the build process. And Selenium and PHPUnit for automated testing.

The Apigee Drupal team's goal is to verify a Drupal point release within 15 days of it being posted on Drupal.org. In practice it's been less time than that as Drupal releases have been getting progressively more stable as they solidify their build processes.
 
##Installation of 7.x-4.0-dev
 
1.  There is a "pear-install.sh" file in the root directory. It will download drush, phing, 
	php-unit and selenium. Run it as root on your machine.
	
	`sudo sh pear-installs.sh`
	
	If you have not yet seen or used automated selenium testing, check it out at saucelabs.com.
	
	Phing is an automated builder for php similar to ANT for Java. It will download all the files
	you need to complete the build process.
     
1.  Install drush registry rebuild.
 
    One big change between Drupal 6 and Drupal 7 is a database table called "registry".
    this table holds the location of all your module files. If those files or any
    of their associated classes for any reason change location your Drupal install 
    will white-screen.
     
    The Phing build script which is in this directory in a file called `build.sh`.
    As part of every build, this shell script instructs Jenkins to do a registry
    rebuild to fix any modules that might have moved since the last build
    and avoid white-screens when file locations change.
     
    if drush is installed correctly, you can simply
     
    `> drush dl registry_rebuild`
 
1.  From the command line, `cd` to the webapp folder
 
1.  Phing
	In the "webapp" folder there's a "build.xml" file. Invoke the phing default build by simply typing `phing -f build.xml`. 
	This will trigger a series of commands resulting in a basic Apigee Drupal install.

1.  Make sure the webserver (typically Apache) can write to sites/default/files. If there's nobody else
    using your server, you can do a chmod -R 777 sites/default/files and that should fix
    any permissions issues you might encounter.

1.  Edit the settings file `sites/default/settings.php`. 

    In the root folder "sites/default" is an example settings.php file. Edit the file with your database connection settings. 
	You should have been given a default portal database from your Apigee Customer service rep along 
	with Portal connection settings based on your enterprise. If you have an existing portal and are setting up for local
	development, you can log into your existing portal and use the Backup/Migrate database export to get a copy
	of your portal. In-house Apigee developers should use the DEVELOPMENT database exports for local development.

1.	Drupal 7 has a setting for "private" files. It's good to not have this private directory in the files
    that are available to the server. I've moved them to /var/cache/drupal and then changed
    the perms on that folder so Apache could write to the directory.
     
1.  Change the admin user's password 
	
	`> drush user-password admin --password='newpass'`
 
    The database backup is in a public repo. Your Drupal install should not be considered secure
    until the password for existing users have been changed. Be sure to follow good password policy 
    and don't write the Admin user's password in a big red binder with 'important passwords' on the outside.
 
1.  Your Drupal install should be ready to use.
