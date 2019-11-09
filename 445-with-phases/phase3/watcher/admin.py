from django.contrib import admin

# Register your models here.
from watcher.models import Watchers, WatcherLogs, WatcherRules

admin.site.register(Watchers)
admin.site.register(WatcherLogs)
admin.site.register(WatcherRules)
