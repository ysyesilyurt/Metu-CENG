from django.shortcuts import render
from django.contrib.auth.decorators import login_required

from watcher.models import Watchers, WatcherLogs, WatcherRules
from util import UDSBuffer, reverseAddress

import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "../util.py")))


# Create your views here.


@login_required
def logs(request, wid=None):
	"""Shows filtered logs of corresponding Watcher instance."""
	filteredLogs = []
	queryRes = WatcherLogs.objects.filter(wid=wid)
	for queryLog in queryRes:
		filteredLogs.append({"log": queryLog.log})
	return render(request, "logs.html", {"filteredLogs": filteredLogs, "lw": "Logwatch " + str(wid)})


@login_required
def rules(request, wid=None):
	"""Shows and updates rules of a Watcher instance."""
	try:
		if request.POST['submit'] == 'SetMatch':
			path = request.POST['path']
			if path == 'NONE':
				path = '()'
			rule = request.POST['rule']
			buffer = UDSBuffer()
			buffer.send("setMatch\n" + wid + "\n" + rule + "\n" + path)
			response = buffer.recv()
			_rules = getRules(wid)
			if response == '0':
				return render(request, "rules.html", {"rules": _rules, "lw": "Logwatch " + str(wid),
													  "op": "setMatch Operation was successful."})
			elif response == '2':
				return render(request, "rules.html", {"rules": _rules, "lw": "Logwatch " + str(wid),
													  "op": "Please fill fields with correct types"})
			else:
				return render(request, "rules.html", {"rules": _rules, "lw": "Logwatch " + str(wid),
													  "op": "setMatch Operation was not successful."})
		elif request.POST['submit'] == 'CombineMatch':
			path = request.POST['path']
			connector = request.POST['connector']
			if path == 'NONE':
				path = '()'
			rule = request.POST['rule']
			buffer = UDSBuffer()
			buffer.send("combineMatch\n" + wid + "\n" + rule + "\n" + connector + "\n" + path)
			response = buffer.recv()
			_rules = getRules(wid)
			if response == '0':
				return render(request, "rules.html", {"rules": _rules, "lw": "Logwatch " + str(wid),
													  "op": "CombineMatch Operation was successful."})
			elif response == '2':
				return render(request, "rules.html", {"rules": _rules, "lw": "Logwatch " + str(wid),
													  "op": "Please fill fields with correct types"})
			else:
				return render(request, "rules.html", {"rules": _rules, "lw": "Logwatch " + str(wid),
													  "op": "CombineMatch Operation was not successful."})
		elif request.POST['submit'] == 'DelMatch':
			path = request.POST['path']
			if path == 'NONE':
				path = '()'
			buffer = UDSBuffer()
			buffer.send("delMatch\n" + wid + "\n" + path)
			response = buffer.recv()
			_rules = getRules(wid)
			if response == '0':
				return render(request, "rules.html", {"rules": _rules, "lw": "Logwatch " + str(wid),
													  "op": "DelMatch Operation was successful."})
			elif response == '2':
				return render(request, "rules.html", {"rules": _rules, "lw": "Logwatch " + str(wid),
													  "op": "Please fill fields with correct types"})
			else:
				return render(request, "rules.html", {"rules": _rules, "lw": "Logwatch " + str(wid),
													  "op": "DelMatch Operation was not successful."})
		else:
			return render(request, 'error.html', {'message': 'Invalid request'})
	except KeyError:
		_rules = getRules(wid)
		return render(request, "rules.html", {"rules": _rules, "lw": "Logwatch " + str(wid)})


@login_required
def index(request, create=None):
	"""Home page which shows active Watcher instances."""
	if create:
		buffer = UDSBuffer()
		buffer.send("create")
		response = buffer.recv()
		watchers = getWatchers()
		if response == '0':

			return render(request, "index.html", {"watchers": watchers, "create": "A new Logwatch instance successfully created."})
		else:
			return render(request, "index.html", {"watchers": watchers, "create": "Failed to create a new Logwatch instance."})
	else:
		watchers = getWatchers()
		return render(request, "index.html", {"watchers": watchers})


def getWatchers():
	watchers = []
	queryWatcher = Watchers.objects.all()
	for watcher in queryWatcher:
		_rules = len(WatcherRules.objects.filter(wid=watcher.wid))
		_logs = len(WatcherLogs.objects.filter(wid=watcher.wid))
		watchers.append({"wid": watcher.wid, "name": watcher.name, "rules": _rules, "logs": _logs})
	return watchers


def getRules(wid):
	_rules = []
	queryRes = WatcherRules.objects.filter(wid=wid).order_by('rule_id')
	for queryRule in queryRes:
		path = tuple(reverseAddress(queryRule.rule_id))
		_rules.append({"rule": queryRule.rule, "path": path})
	return _rules
