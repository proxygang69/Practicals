import { bootstrapApplication } from '@angular/platform-browser';
import { AppComponent } from './app/app.component';
import { AppRoutes } from './app/app.routes';

bootstrapApplication(AppComponent, {
  providers: [AppRoutes]
});
