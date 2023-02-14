import urllib
import re
import json
import urllib.request, os

class Github():
   def __init__(self, projectName):
       self.repo_owner = 'XERGER'
       self.repo_name = projectName
       self.access_token = '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'
       repo_name = re.sub(r'\.git$','',os.path.basename('https://github.com/XERGER/demo_cmake.git') )
       print(repo_name)

   def createRelease(self, version, filePath, description, draft=True):
       print('upload to github')
       upload_url = self.createTagAndGetUploadUrl(version, description, draft)

       hdl = open(filePath, 'rb')
       upload_req = urllib.request.Request(upload_url,
           data = hdl.read(),
           headers = {
           'Authorization' : 'token %s' % (self.access_token),
           'Content-Type' : 'application/zip'
           }
       ) 
       with urllib.request.urlopen( upload_req ) as f:
           upload_response = json.loads( f.read().decode('utf-8') )

   def createTagAndGetUploadUrl(self, version, description, draft):
       request_url = 'https://api.github.com/repos/%s/%s/releases' % (self.repo_owner, self.repo_name)
 
       request_data = urllib.request.Request(request_url,
           data = json.dumps({
			'tag_name': "v%s" % (version),
			'name': "v%s" % (version),
			'body': description,
			'draft': draft
			#'prerelease': bool(args.pre)
           }).encode('utf-8') ,
           headers = {
              'Accept': 'application/vnd.github+json',
              'Authorization': 'Bearer %s' % self.access_token,
           } )

       with urllib.request.urlopen(request_data) as f:
            api_response = json.loads( f.read().decode('utf-8') )

       return '%s?name=%s.AppImage' % ( re.sub( r'{\?.*}$', '', api_response['upload_url'] ), self.repo_name )