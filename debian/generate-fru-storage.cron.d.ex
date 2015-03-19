#
# Regular cron jobs for the generate-fru-storage package
#
0 4	* * *	root	[ -x /usr/bin/generate-fru-storage_maintenance ] && /usr/bin/generate-fru-storage_maintenance
