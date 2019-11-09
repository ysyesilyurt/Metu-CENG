from django.urls import path, re_path
import multiprocessing
import sys
from . import views

urlpatterns = [
    path("", views.index, name='index'),
    path("create/", views.index, {"create": True}, name="create"),
    re_path(r"^logs/(?P<wid>[0-9]+)$", views.logs, name='logs'),
    re_path(r"^rules/(?P<wid>[0-9]+)$", views.rules, name='rules')
]
